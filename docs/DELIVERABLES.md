# Project deliverables

Two parts. **Part A** is the Required MVP for the class: three computer-vision
deliverables, scoped to a lean version that fits **2 weeks (aggressive) to 4 weeks
(with buffer)**. **Part B** is the long-range
roadmap (3+ months, built to teach DL/ML, CV and embedded concepts in depth).
Part B is optional and independent of grading.

Technical detail for Part A lives in [`CV_DELIVERABLES.md`](CV_DELIVERABLES.md).
Embedded work lives in [`HARDWARE_DELIVERABLES.md`](HARDWARE_DELIVERABLES.md).

Time estimates are rough, for one person working part-time alongside other projects.
Nothing in Part B has been implemented. The embedded items are meant to be written by you.

---

# Part A: Required MVP (for the class)

**One sentence for your teacher:** *"In simulation, I generate a labelled dataset
automatically, fine-tune and score a YOLO detector (mAP), calibrate the camera and
hand-eye transform against known ground truth, and estimate 6-DoF object poses
from depth and measure the error against ground truth."*

This is the agreed core, scaled to its minimum. The three deliverables and their
headline metrics are unchanged; only the extras around them were cut (see the table
below). Extras are listed as optional so they can be added back if time allows.

## The three agreed deliverables

| # | Deliverable (as agreed) | Headline metric (must report) | Lean scope |
|---|---|---|---|
| R1 | Camera calibration + hand-eye calibration | Intrinsics error vs ground truth; hand-eye translation (mm) and rotation (deg) error vs URDF ground truth; reprojection RMS (px) | ChArUco/checkerboard, ~15 arm poses, `cv2.calibrateCamera` + `cv2.calibrateHandEye` (2 methods) |
| R2 | Synthetic labelled dataset + fine-tuned YOLO | mAP@0.5 and mAP@0.5:0.95 on a held-out test split | ~1,500 simulator-labelled images, 2-3 object classes, YOLOv8n, ~30 epochs on a Colab T4 |
| R3 | 6-DoF pose from depth vs ground truth | Median translation error (mm), median rotation error (deg) | YOLO box -> crop depth -> remove table plane -> PCA init -> ICP to the object mesh, scored on ~100-200 frames |
| R4 | Short report + one-command reproduction | Three tables, one per deliverable | 3-5 pages, no new experiments |

## What was cut, and why it is safe to cut

| Removed from the earlier plan | Reason |
|---|---|
| Domain-shifted test split | A second split is optional for the agreed claim. Mention as a limitation instead. |
| HSV-colour baseline comparison | Nice-to-have comparison; not part of the agreed metric. |
| Error-vs-depth-noise plot | Extra analysis; not part of the agreed metric. |
| Error-vs-number-of-poses study for calibration | Extra analysis. Report one run. |
| Instance segmentation, more classes, large dataset | Scope growth. 2-3 classes is enough to show mAP. |
| Multi-method pose comparison (PCA vs ICP vs learned) | Report ICP (with PCA init) only. |
| Gazebo bounding-box sensor | Replaced by projecting known object poses through the camera model. Simpler and has fewer moving parts. |
| Long report | Three tables and a short limitations paragraph. |

Retained on purpose: simulator-generated labels, scene-level train/val/test split
(no leakage), ground-truth comparison for both calibration and pose, and ADD-S for
symmetric objects if a cylinder is used. These are what make the numbers meaningful.

## Design decisions that keep it small

1. **One camera for everything.** Use the wrist camera (`wrist_camera:=true`, eye-in-hand)
   with a checkerboard placed on the table. Calibration gives `T_tool_cam`; pose in the
   robot base frame is `T_base_tool * T_tool_cam * T_cam_object`. This makes the three
   deliverables share one pipeline instead of three separate ones.
   *Fallback if the wrist camera topics are not working on day 1:* use the fixed head
   camera in an eye-to-hand setup (checkerboard on the tool); `cv2.calibrateHandEye` is
   used the same way with inverted robot poses.
2. **Labels from geometry.** Each object's pose is known to the simulator; project its 3D
   box corners through the intrinsics to get a 2D box. Keep objects non-overlapping to
   avoid occlusion handling.
3. **A few fixed viewpoints, many randomised scenes.** Move the arm to ~8 preset poses,
   and at each one randomise object poses, colours and lighting for ~190 frames. The arm
   moves 8 times, not 1,500.
4. **Develop R3 with ground-truth boxes first,** then swap in YOLO boxes once R2 finishes.
   This removes the dependency between the tracks.
5. **Leave heavy jobs running in the background.** Data capture runs unattended; YOLO
   training runs on Colab. Your hands-on time goes to the other tracks meanwhile.

## Working on all three at once

After a short shared setup, the tracks are independent until the last step.

```
Days 1-2   SHARED SETUP (gate)      sim runs headless · camera topics + intrinsics read ·
                                    ground-truth object poses logged · arm moves to preset poses
              |
   +----------+-----------+----------------------+
   | R1 calibration       | R2 dataset + YOLO     | R3 pose from depth
   | Days 3-6             | Days 3-10             | Days 4-11
   | capture, solve,      | build randomiser,     | write estimator on GT boxes,
   | compare to URDF      | capture overnight,    | metrics (ADD-S, rot/trans),
   |                      | train on Colab, mAP   | then swap in YOLO boxes
   +----------+-----------+----------------------+
              |
Days 12-14  INTEGRATE + REPORT      use calibrated transform in R3 · three tables · README
```

## Schedule

**2-week plan (aggressive).** Assumes about 15-20 focused hours a week for this project
and that the simulator already runs on your machine.

| Days | Work | Done when |
|---|---|---|
| 1-2 | Shared setup: headless sim, camera topics, intrinsics, GT pose logging, preset arm poses | A script saves one image + depth + GT poses + joint state |
| 3-6 | R1: place checkerboard, capture ~15 poses, solve, compare to URDF | Table of intrinsics and hand-eye errors |
| 3-4 | R2: dataset script (randomise, project boxes, YOLO export) | 50 images generated and visually checked |
| 5-8 | R2: full capture running in the background; set up Colab; train; evaluate | mAP table from the held-out test split |
| 4-11 | R3: depth crop, plane removal, PCA + ICP, metrics on GT boxes then YOLO boxes | Median translation/rotation error table |
| 12-13 | Integrate calibrated transform; rerun R3 end to end | Same table, now using calibration output |
| 14 | Report, README, reproduction commands | Teacher-ready package |

**4-week plan (with buffer).** Same work, same order, but each block gets about double the
time, with a full buffer week for environment problems, a retrain, or a rerun.

## Go / no-go checkpoints

| When | Check | If it fails |
|---|---|---|
| End of day 2 | A saved frame has image, depth and correct GT poses | Stop and fix; everything depends on this. Switch to the head-camera fallback if the wrist topics fail. |
| Day 6 | Calibration gives sane numbers (error well below a few mm / a degree or two in sim) | Check frame conventions before anything else; this is the most common bug. |
| Day 8 | YOLO mAP above zero and boxes line up with images when drawn | Check label formatting and the scene-level split before retraining. |
| Day 11 | Pose estimator works on GT boxes | Fall back to PCA-only and report ICP as future work. |

## Acceptance criteria (minimum "done")

**R1 Calibration**
- [ ] Checkerboard/ChArUco in the world; about 15 diverse arm poses captured.
- [ ] Intrinsics from `cv2.calibrateCamera`, compared to the simulator's `camera_info`.
- [ ] Hand-eye from `cv2.calibrateHandEye` with two methods; errors vs the URDF reported in mm and degrees.
- [ ] Result published as a TF or saved config used by R3.
- [ ] The URDF value was not copied into the "calibrated" result.

**R2 Dataset + YOLO**
- [ ] Simulator-generated labels for ~1,500 images with randomised poses, colours and lighting.
- [ ] YOLO-format export, split by scene (no frames from one scene in two splits).
- [ ] YOLOv8n trained in Colab; weights saved.
- [ ] mAP@0.5 and mAP@0.5:0.95 on the held-out test split, plus per-class AP.
- [ ] A few overlay images showing predictions, including at least one failure case.

**R3 Pose**
- [ ] Ground-truth object poses expressed in the camera frame.
- [ ] Depth crop -> plane removal -> PCA init -> ICP to the object mesh.
- [ ] Median translation (mm) and rotation (deg) error on 100-200 frames; ADD-S if an object is symmetric.
- [ ] Final run uses YOLO boxes and the calibrated transform.

**R4 Report**
- [ ] One script or notebook per table, fixed seeds, versions recorded.
- [ ] Short limitations paragraph: simulation only, synthetic test data, objects not overlapping.

## Optional extras (only if time remains)

Domain-shifted test split; HSV baseline; depth-noise plot; calibration error vs number of
poses; head-camera eye-to-hand calibration as well; Gazebo bounding-box sensor instead of
projected labels. These were in the earlier 6-8 week version.

## Main risks

| Risk | Mitigation |
|---|---|
| Simulator/ROS environment does not run on your laptop | Resolve first; use headless mode and low resolution. Everything else waits on this. |
| Wrist-camera bridge topics are unverified in the repo (a comment in `ros_gz_bridge.yaml` says the link path is a guess) | Check on day 1; use the head-camera fallback. |
| Frame-convention mistakes in calibration | Test the pipeline on synthetic data with a known answer before using simulator output. |
| Colab limits or disconnects | Save checkpoints to Google Drive each epoch group; keep training short. |
| Time estimates assume focused work and no environment surprises | The 4-week plan exists for this reason. |

---

# Part B: Roadmap beyond the MVP

Items are grouped by track. Each has a tier:

- **MVP+** : a natural next step after Part A, 1-3 weeks.
- **Advanced** : a few weeks to a month, needs the MVP+ items in its track.
- **Stretch** : large, research-flavoured or hardware-dependent; one to several months.

Each item says what it teaches, so you can choose by skill rather than by order.
IDs are stable references (CV-3, ML-5, ...).

## Track CV: Computer vision

| ID | Tier | Item | What it teaches | Done when |
|---|---|---|---|---|
| CV-1 | MVP+ | Classical pipeline from scratch: HSV, morphology, contours, Hough | Why classical methods work, and where they break | Beats/loses to YOLO with a measured reason |
| CV-2 | MVP+ | Stereo depth from the simulated infra1/infra2 cameras (block matching, SGBM) | Epipolar geometry, disparity, depth error vs baseline | Depth map error vs simulator ground truth |
| CV-3 | MVP+ | Point-cloud processing in Open3D: filtering, normals, RANSAC planes, clustering | 3D data structures and robust fitting | Segment objects without colour |
| CV-4 | Advanced | Feature-based pose: keypoints, descriptors, PnP + RANSAC against a known object | Classical 6-DoF, outlier rejection | Pose error vs R3 baseline |
| CV-5 | Advanced | Instance segmentation (YOLO-seg or Mask R-CNN) using Gazebo segmentation-camera labels | Pixel-level labels, mask quality metrics | mask mAP; masks replace boxes in R3 |
| CV-6 | Advanced | Multi-view fusion + TSDF reconstruction of an object | Pose graphs, volumetric fusion | Mesh compared to ground-truth CAD |
| CV-7 | Advanced | Visual servoing (IBVS and PBVS) closed on live detections | Image Jacobian, control from vision | Convergence plots, final pixel error |
| CV-8 | Advanced | Object tracking (Kalman filter + data association, then a learned tracker) on a conveyor | State estimation, MOT metrics | MOTA/IDF1 on the conveyor sim |
| CV-9 | Advanced | Learned 6-DoF pose (keypoint or direct regression network) trained on synthetic data | Pose networks, sim-to-real gap | Beats ICP baseline on a hard split, or explains why not |
| CV-10 | Advanced | Learned grasp quality from depth (e.g. a small grasp CNN) | Dense prediction, grasp metrics | Success rate in sim vs analytic grasps |
| CV-11 | Stretch | SLAM / visual odometry (ORB features or a library) from the wrist camera | Multi-view geometry, bundle adjustment | Trajectory error (ATE) vs ground truth |
| CV-12 | Stretch | Neural scene representation (NeRF or Gaussian splatting) of the workspace | Differentiable rendering | Novel-view PSNR |
| CV-13 | Stretch | Foundation models (open-vocabulary detection, SAM-style segmentation) vs your YOLO | Zero-shot vs fine-tuned trade-offs | Comparison on your benchmark |
| CV-14 | Stretch | Sim-to-real study on a few real photos of similar objects | Domain gap, augmentation, adaptation | Measured drop and what recovers it |

## Track ML: Deep learning and machine learning

Build things by hand before using libraries, then compare.

| ID | Tier | Item | What it teaches | Done when |
|---|---|---|---|---|
| ML-1 | MVP+ | Experiment hygiene: seeds, config files, run logging (TensorBoard or W&B), data versioning | Reproducibility, the habit that separates projects from demos | Any past result re-runs from one command |
| ML-2 | MVP+ | Metrics deep dive: IoU, precision/recall, PR curves, mAP implemented yourself | What the number actually means | Your mAP matches Ultralytics within tolerance |
| ML-3 | MVP+ | Data analysis: class balance, box-size distribution, leakage checks, label-noise audit | Most real failures are data failures | One-page dataset card |
| ML-4 | Advanced | Train a small CNN classifier from scratch in PyTorch (no pretrained weights) | Backprop, optimisers, overfitting, augmentation | Learning curves; ablations of each choice |
| ML-5 | Advanced | Re-implement a tiny detector (anchor-free, single scale) | Detection heads, losses, NMS | Reasonable mAP on a simple split |
| ML-6 | Advanced | Ablation studies on YOLO: augmentation, image size, model size, freeze layers | Scientific method on models | Table of effects with confidence intervals (multiple seeds) |
| ML-7 | Advanced | Domain randomisation study: which randomisations matter | Sim-to-real levers | Ranked effect sizes |
| ML-8 | Advanced | Model optimisation: pruning, quantisation (INT8), ONNX export, latency benchmark | Deployment under constraints | Accuracy vs latency Pareto plot |
| ML-9 | Advanced | Active learning / hard-example mining loop in the simulator | Data-centric ML | mAP gain per labelled image vs random |
| ML-10 | Advanced | Uncertainty and calibration (ensembles or MC dropout, reliability diagrams) | When a model knows it is wrong | ECE reported; low-confidence frames rejected |
| ML-11 | Advanced | Imitation learning: behaviour cloning, then ACT or Diffusion Policy on recorded demos | Policy learning from demonstrations | Success rate in sim vs scripted baseline |
| ML-12 | Advanced | Reinforcement learning study: SAC/PPO on the reach task, reward design | Exploration, reward shaping, instability | Learning curves over multiple seeds |
| ML-13 | Stretch | Learned dynamics / world model of the arm | Model-based RL, compounding error | Multi-step prediction error |
| ML-14 | Stretch | Vision-language-action: fine-tune and evaluate a VLA on your demos | Large-model adaptation, evaluation difficulty | Success rate vs BC baseline, with honest failure analysis |
| ML-15 | Stretch | MLOps: CI that retrains/evaluates on a tiny dataset, model registry, regression gates | Shipping ML safely | A PR that lowers mAP fails CI |
| ML-16 | Stretch | Write a short paper-style report of one study with ablations | Scientific writing | Reviewable PDF |

## Track EMB: Embedded and real-time

Details, code and bring-up in [`HARDWARE_DELIVERABLES.md`](HARDWARE_DELIVERABLES.md).

| ID | Tier | Item | What it teaches |
|---|---|---|---|
| EMB-1 | MVP+ | Write a portable C servo core yourself (PID, CRC-16, framing, ring buffer, fault FSM) with host-side unit tests | Portable firmware design, testing without hardware |
| EMB-2 | MVP+ | Simulated joint drive: motor + encoder model driving your servo core | Plant modelling, control tuning |
| EMB-3 | MVP+ | `ros2_control` `SystemInterface` C++ plugin wrapping the servo core | The real hardware boundary in ROS 2 |
| EMB-4 | Advanced | Virtual CAN (`vcan`) bus and a drive-simulator process speaking your framing | Protocols, message loss, ordering |
| EMB-5 | Advanced | Real-time-safe update loop: no allocation, bounded time, jitter measurement | Determinism, latency budgets |
| EMB-6 | Advanced | Fault injection tests (dropped frames, stuck encoder, overcurrent, latency spikes) | Failure-mode thinking |
| EMB-7 | Advanced | Fixed-point PID and cycle/size budget on a Cortex-M class target | Resource-constrained numerics |
| EMB-8 | Advanced | Trajectory generation on the MCU: trapezoidal and S-curve profiles | Motion profiles, jerk limits |
| EMB-9 | Advanced | RTOS tasks (FreeRTOS or Zephyr): control task, comms task, watchdog, priorities | Scheduling, priority inversion |
| EMB-10 | Advanced | Bootloader-safe firmware update with CRC check and rollback | Field reliability |
| EMB-11 | Stretch | Field-oriented control (FOC) of a BLDC in simulation, then on a bench motor | Motor control theory |
| EMB-12 | Stretch | Hardware-in-the-loop: the same firmware on a dev board, plant simulated on the PC | Closing the sim-to-hardware gap |
| EMB-13 | Stretch | Sensor fusion on the MCU (IMU + encoder, complementary or Kalman filter) | Estimation under noise |
| EMB-14 | Stretch | Safety concept: e-stop chain, safe-torque-off, limit enforcement below software, a written hazard analysis | Functional-safety thinking |
| EMB-15 | Stretch | Bring up a real low-cost arm joint or gripper end to end | Everything, on hardware |

## Track SW: Software engineering and robotics (the refactor)

| ID | Tier | Item | What it teaches |
|---|---|---|---|
| SW-1 | MVP+ | CI: `colcon test`, `ruff`, `clang-format`, `clang-tidy` on every PR | Automation instead of discipline |
| SW-2 | MVP+ | Pin one supported ROS + Gazebo pairing; fix README/INSTALL contradictions | Dependency management |
| SW-3 | MVP+ | Characterisation tests on existing behaviour before touching it | Safe refactoring |
| SW-4 | MVP+ | Replace `print()` with loggers, remove silent `except: pass` | Error handling, observability |
| SW-5 | Advanced | Remove duplicated packages and files (`object_segmentation.cpp` exists twice) | Maintainability |
| SW-6 | Advanced | Per-arm YAML config (joints, limits, named poses, gripper) replacing UR3 hardcoding | Abstraction and configuration |
| SW-7 | Advanced | FANUC as a selectable arm in the same sim (see below) | Generalising a codebase |
| SW-8 | Advanced | Lifecycle nodes, composition, parameter validation | Idiomatic ROS 2 |
| SW-9 | Advanced | Separate pure logic from ROS nodes and unit-test it | Testable design |
| SW-10 | Stretch | Behaviour-tree task layer over the perception outputs | Task-level autonomy |
| SW-11 | Stretch | Docker/devcontainer for one-command setup, including a Colab-compatible data path | Reproducible environments |
| SW-12 | Stretch | Real-arm driver abstraction (UR RTDE and FANUC) behind one interface | Hardware abstraction |

### FANUC (SW-7), plan

Goal: the same pick-and-place runs with a UR3 or a FANUC arm, selected by config.
Candidate: **CRX-10iA/L** (collaborative; I believe it has an official ROS 2 driver, but that
was not verified against the source, so check first). Alternative: LR Mate 200iD or M-10iA
through the BSD-licensed `moveit_resources_fanuc_description`.
Steps: confirm model with the target job postings; find a maintained URDF/meshes; write the
arm config (SW-6); add SRDF and controllers; get the arm moving in Gazebo with mock
hardware first; then run the existing MTC pipeline. Open question: Gazebo support for the
CRX packages is unconfirmed. Real hardware needs FANUC controller options not available
in simulation.

## Suggested paths

- **Vision engineer path:** Part A, CV-2, CV-3, CV-4, CV-5, CV-9, CV-7, CV-13.
- **ML engineer path:** Part A, ML-1, ML-2, ML-3, ML-4, ML-6, ML-8, ML-10, ML-11.
- **Embedded/robotics path:** Part A, EMB-2 to EMB-6, SW-1, SW-6, EMB-8, EMB-9, EMB-12.
- **Balanced three-month path:** Part A, then ML-1, ML-2, CV-3, EMB-2, EMB-3, SW-1, SW-6, ML-6, CV-5, EMB-5.
