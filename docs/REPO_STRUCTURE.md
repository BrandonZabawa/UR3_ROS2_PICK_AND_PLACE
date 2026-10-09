# Target repository structure

A design for turning this repo, and any later robotics repo, into something that reads
as a professional software suite. It is a proposal; nothing here has been migrated.

The idea in one line: **structure should answer three questions in under a minute:
what does it do, does it work, and can I run it.** Folders help with the first. CI,
tests and published results answer the other two, and they matter more than the layout.

## 1. Layer diagram (dependencies point downward only)

```
        +--------------------------------------------------------------+
        |  applications/   pick_place · sorting · conveyor · demos     |
        +------------------------------+-------------------------------+
                                       |
        +-----------+-----------+------+------+-------------+----------+
        | perception| planning  |  control    |  learning   |   ui     |
        | calibrat. | MoveIt/   | controllers |  ml/ (train |dashboard |
        | detection | MTC / BT  | hw plugins  |  & eval)    |          |
        | pose est. |           |             |             |          |
        +-----------+-----+-----+------+------+------+------+----------+
                          |            |             |
        +-----------------+------------+-------------+----------------+
        |  robots/   per-arm config: ur3 · fanuc_crx · grippers        |
        |  (description, joint limits, named poses, moveit, ros2_ctrl) |
        +------------------------------+-------------------------------+
        |  interfaces/   msgs · srvs · actions   (no logic)            |
        +------------------------------+-------------------------------+
        |  simulation/ worlds · sensors · dataset generator            |
        |  firmware/   portable C core · platform ports · HIL          |
        +--------------------------------------------------------------+
```

Rules that keep it clean:
- A package may depend on layers below it, never above or sideways within the same layer
  without a reason written in an ADR.
- Only `robots/` knows arm-specific numbers. Everything else reads them from config.
- `interfaces/` holds message definitions only, so any package can depend on it cheaply.
- `firmware/` has no ROS dependency. It talks to ROS only through a documented wire protocol.

## 2. Top-level layout

```
robotics-suite/
├── README.md                  hero demo GIF, architecture diagram, quick start, results table
├── LICENSE
├── CITATION.cff               makes the repo citable
├── CONTRIBUTING.md            how to build, test, lint, open a PR
├── SECURITY.md  CODE_OF_CONDUCT.md  CHANGELOG.md
│
├── .github/
│   ├── workflows/             ci.yml (lint+build+test) · docs.yml · release.yml
│   ├── ISSUE_TEMPLATE/  PULL_REQUEST_TEMPLATE.md  CODEOWNERS  dependabot.yml
├── .devcontainer/             one-click dev environment (VS Code / Codespaces)
├── docker/                    Dockerfile(s): ros-base, sim, ml-train
├── .pre-commit-config.yaml    runs ruff, clang-format, markdownlint, codespell
├── .clang-format  .clang-tidy  .editorconfig  pyproject.toml (ruff, pytest config)
├── deps.repos                 vcstool list of external ROS repos (replaces vendoring)
│
├── docs/
│   ├── index.md  mkdocs.yml
│   ├── architecture/          diagrams, data flow, frames/TF tree
│   ├── adr/                   Architecture Decision Records (0001-use-ros2-control.md ...)
│   ├── guides/                install, quick start, calibration, adding a new arm
│   ├── results/               benchmark tables and plots with how to reproduce them
│   └── hardware/              wiring, bring-up checklist, safety notes
│
├── robots/                    ── one folder per arm; the abstraction layer ──
│   ├── ur3/                   description/  moveit_config/  controllers/  arm.yaml
│   ├── fanuc_crx/             same shape as ur3
│   └── grippers/              robotiq_2f_85/  onrobot_rg2/ ...
│
├── src/                       ── ROS 2 packages (colcon finds them at any depth) ──
│   ├── interfaces/            suite_interfaces/
│   ├── simulation/            suite_gazebo/  suite_worlds/  suite_dataset_gen/
│   ├── perception/            suite_calibration/  suite_detection/  suite_pose_estimation/
│   ├── planning/              suite_moveit_bringup/  suite_mtc_tasks/  suite_bt/
│   ├── control/               suite_hardware_interface/  suite_controllers/  suite_force_control/
│   ├── learning_ros/          suite_policy_runtime/  suite_data_collector/
│   ├── ui/                    suite_dashboard/
│   └── applications/          suite_pick_place/  suite_sorting/  suite_conveyor/
│
├── ml/                        ── not ROS; trainable in Colab / any GPU box ──
│   ├── configs/               YAML per experiment (seeds, hyperparameters)
│   ├── datasets/              loaders, format converters, dataset cards
│   ├── models/                detector, pose net, policies
│   ├── training/              train.py, eval.py (same CLI everywhere)
│   ├── notebooks/             Colab entry points that call training/ (thin)
│   ├── experiments/           run logs and reports (weights NOT in git)
│   └── pyproject.toml
│
├── firmware/                  ── embedded, no ROS ──
│   ├── core/                  portable C: pid, crc, framing, ringbuf, fault_fsm
│   │   ├── include/  src/  test/        host unit tests, run under sanitizers
│   ├── platform/              stm32/  rp2040/  linux_sim/   (HAL ports, drivers, linker scripts)
│   ├── sim/                   motor + encoder model, vcan bridge
│   ├── hil/                   hardware-in-the-loop scripts and fixtures
│   └── CMakeLists.txt
│
├── tests/
│   ├── integration/           launch_testing: bring up sim, run a task, assert
│   ├── system/                end-to-end scenarios with pass/fail criteria
│   └── data/                  tiny fixtures only
│
├── benchmarks/                reproducible scripts that generate docs/results tables
├── tools/                     dev scripts: setup, format, generate dataset, plot
└── external/                  vcs-imported deps (gitignored)
```

Every package under `src/` has the same shape:

```
suite_calibration/
├── package.xml  CMakeLists.txt | setup.py
├── README.md                  purpose, topics/services, parameters, example
├── config/  launch/  include|python/  src/
└── test/                      unit tests (pure logic) + launch tests
```

## 3. Mapping from the current repo

| Today | Target | Note |
|---|---|---|
| `ur_description`, `moveit_config` | `robots/ur3/` | split UR-only config out of shared code |
| `robotiq_description`, `onrobot_description`, `robotiq_2f_85_gripper_visualization` | `robots/grippers/` | |
| (new) FANUC | `robots/fanuc_crx/` | same shape as `robots/ur3/` |
| `ur_interfaces` | `src/interfaces/suite_interfaces` | |
| `ur_gazebo` | `src/simulation/suite_gazebo`, `suite_worlds` | |
| `ur_perception` + `ur_grasp` | `src/perception/` | split into calibration, detection, pose estimation |
| `ur_mtc_pick_place_demo`, `ur_mtc_demos`, `ur_moveit_demos` | `src/planning/`, `src/applications/` | de-duplicate; two copies of `object_segmentation.cpp` exist |
| `ur_bt_planner` | `src/planning/suite_bt` | |
| `ur_force_control`, `ur_visual_servo` | `src/control/` | |
| `ur_rl_training`, `mujoco_ur_rl_ros2`, `ur_flow_policy`, `ur_openvla` | `ml/` + `src/learning_ros/` | training code leaves ROS; only runtime stays |
| `ur_data_collector` | `src/learning_ros/` | exporter scripts go to `ml/datasets/` |
| `ur_llm_planner`, `ur_voice_cmd` | `src/applications/` (optional) | label experimental |
| `ur_conveyor`, `ur_sorting_demo` | `src/applications/` | |
| `ur_web_dashboard` | `src/ui/` | |
| `ur_system_tests`, `testing/` | `tests/` | convert scripts to real tests |
| `src/moveit_task_constructor`, `gz_ros2_control`, `warehouse_ros_mongo` | `deps.repos` | stop vendoring unless you must patch; if patched, keep a fork and pin a commit |
| `docs/BUGS_FIXED.md` etc. | `docs/` + `CHANGELOG.md` | |

Migrating is large and risky. Do it in small PRs: CI first, then one layer at a time,
with the launch and tests green after each.

## 4. What reviewers should see in 60 seconds

1. README with a demo GIF, a one-paragraph claim, an architecture diagram, and a results
   table with real numbers and a link to the script that produced them.
2. A green CI badge, and CI that actually runs lint, build and tests.
3. `docs/adr/` showing that decisions were weighed (e.g. why vcstool over vendoring).
4. A `docs/guides/adding-a-new-arm.md` that demonstrates the abstraction is real.
5. Tests next to the code, and a `CONTRIBUTING.md` that tells a stranger how to run them.
6. A `firmware/` folder with host-run unit tests and a stated honesty line about what
   has and has not been run on hardware.

## 5. Reusing this approach on other robotics repos

Keep the same skeleton and shrink it to fit:

- Always: `README.md`, `LICENSE`, CI workflow, `.pre-commit-config.yaml`, `docs/`, `tests/`.
- Add `robots/` only when you support more than one robot.
- Add `ml/` only when you train models; keep it free of ROS imports.
- Add `firmware/` only when you ship embedded code; keep it free of ROS imports.
- Use the same layer names across repos so people recognise them.

## 6. Cautions

- Structure does not make a project good. An empty tidy tree with no tests looks worse
  than a messy repo that works and is verified. Build CI and tests before moving folders.
- Over-structuring a small repo is a common mistake. Introduce a folder when it has two
  or more things to put in it.
- Do not commit large files (weights, bags, datasets). Use Git LFS, DVC, or release assets.
- Moving packages changes their paths and can break launch files and `package://` URIs.
  Check every `find_package`, `$(find ...)` and `get_package_share_directory` use.
- colcon finds packages at any depth, but a stray `package.xml` inside `external/` or a
  build tree will be picked up unless you add a `COLCON_IGNORE` file.
