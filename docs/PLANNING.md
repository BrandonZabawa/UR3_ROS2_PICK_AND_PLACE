# Planning cadence: monthly, bi-weekly, weekly, daily

A working plan for running several robot projects at once, packing as many concepts
as possible into each robot, and leaving visible evidence (board, repo, website) of
what got done.

Calendar starts **Monday 12 October 2026**. Sprints are two weeks; milestones close
every second sprint (about monthly).

## Assumptions (edit these first)

| Item | Assumed | Notes |
|---|---|---|
| Hours per week, all projects | ~25-30 | Adjust and rescale the tables below |
| Class MVP weeks | 15-20 h/week for 2 weeks | Then drops to report polishing |
| Hardware track | 4-6 h/week | Rises after the class MVP |
| Viable Solutions arm | **unknown** | Placeholder rows marked `VS-?`; fill them in from that project |
| Board + website + devlog | ~2 h/week | Fridays |

---

## 1. The robots and what each one carries

Three robots, each loaded with as many concepts as it can hold. The rule: **every
monthly milestone on a robot must exercise at least two tracks** (for example
embedded + control + modelling), so no month produces a single-skill result.

| Robot | Role | Tracks it carries |
|---|---|---|
| **R-SIM: UR3 suite (this repo)** | Software/vision/ML flagship | CV, DL/ML, ROS 2, MoveIt, software engineering, FANUC as a second arm config |
| **R-HW: custom arm (new repo)** | Embedded/hardware flagship | Firmware, PCB, motor control, CAN, RTOS, system identification, ros2_control hardware interface |
| **R-VS: Viable Solutions arm** | Industrial/integration | Whatever that project requires; link its deliverables here as `VS-*` |

The three link to each other on purpose:
- R-HW's measured motor data feeds R-SIM's simulator (system identification, HW-11).
- R-SIM's calibration and pose code runs on R-HW's camera later (HW-17).
- R-SIM's arm-config layer (SW-6) is how R-HW and FANUC become selectable arms.

### Concept-density matrix

`●` = core concept on that robot, `○` = secondary.

| Concept | R-SIM | R-HW | R-VS |
|---|---|---|---|
| Camera + hand-eye calibration | ● | ○ | ? |
| Detection (YOLO), datasets, mAP | ● |  | ? |
| 6-DoF pose, point clouds, ICP | ● | ○ | ? |
| Training, ablations, quantisation, deployment | ● | ○ | ? |
| Imitation / reinforcement learning | ○ |  | ? |
| Motion planning (MoveIt, MTC) | ● | ○ | ? |
| ros2_control (controllers + hardware interface) | ○ | ● | ? |
| Firmware: timers, PWM, ADC/DMA, interrupts | | ● | ? |
| Buses: CAN, UART, SPI | | ● | ? |
| Motor control: PID, FOC | | ● | ? |
| RTOS, timing, WCET | | ● | ? |
| PCB design and bring-up | | ● | ? |
| Safety: e-stop, watchdog, fault handling | ○ | ● | ? |
| System identification, sim-to-real | ● | ● | ? |
| CI, tests, code quality, docs | ● | ● | ? |

Fill the R-VS column from that project; gaps in the other columns show where it adds the most.

---

## 2. Cadence

| Level | Length | Output (must exist when it ends) | Where it is recorded |
|---|---|---|---|
| **Milestone** | ~4 weeks (2 sprints) | One demonstrable result per active robot: tagged release, demo video or GIF, results plot/table | GitHub milestone + release, website project page |
| **Sprint** | 2 weeks | One sprint goal per active robot; merged PRs; short sprint review note | Project board iteration, `docs/devlog/` sprint note |
| **Week** | 7 days | 3-6 closed issues; one devlog entry | Board, devlog, website (weekly post optional) |
| **Day** | one work session | 1 main task + 1 small task, each ends in a commit, PR, or issue update | Issue comments, commit history |

### Definition of done (applies at every level)

An item is done only when it has **evidence attached**: a merged PR, a test result, a
plot, a photo, or a video, linked in the issue's "Evidence" field. No evidence, not done.

### Weekly rhythm

| Day | Activity |
|---|---|
| Monday | 30-minute planning: pick the week's issues from the sprint, size them |
| Tue-Thu | Build. Hardest task of the week early in the week |
| Friday | Verify, close issues with evidence, write devlog entry, update board and website |
| Weekend | Buffer or long uninterrupted blocks (hardware bench work fits here) |

### Daily rhythm

1. Pick **one main task** (2-4 h) and **one small task** (≤30 min, e.g. a doc fix or test).
2. Work on a branch; commit at least once.
3. End with a one-line log comment on the issue: what changed, what's next, what's blocked.

Tasks bigger than ~4 h get split before they are started.

---

## 3. Monthly milestones (first six months)

| Milestone | Dates | R-SIM | R-HW | R-VS | Portfolio |
|---|---|---|---|---|---|
| **M1** | 12 Oct - 8 Nov 2026 | Class MVP R1-R4 done and presented | HW-1 bench + safety; parts ordered; HW-2 dev-board bring-up started | VS-? | Board live; website v1 (home, 3 project pages, devlog) |
| **M2** | 9 Nov - 6 Dec | SW-1 CI, SW-2 pinned environment, SW-3 characterisation tests, ML-1 experiment hygiene | HW-2 done; HW-3 closed-loop DC motor with step-response plot | VS-? | Post: "Class CV results" write-up |
| **M3** | 7 Dec - 3 Jan 2027 | SW-4 logging cleanup, ML-2 own mAP implementation, CV-3 point clouds | EMB-2 motor model in sim compared against HW-3 data; HW-4 CAN node | VS-? | Post: "Sim vs real motor" with plots |
| **M4** | 4 Jan - 31 Jan | SW-6 per-arm config, SW-9 logic split from nodes | HW-5 ros2_control interface moves the real joint from ROS 2 | VS-? | Demo video: ROS 2 driving your own joint |
| **M5** | 1 Feb - 28 Feb | SW-7 FANUC as a selectable arm in sim; ML-6 YOLO ablations | HW-6 safety + telemetry; HW-7 hardware MVP write-up | VS-? | Release: hardware MVP v1.0 |
| **M6** | 1 Mar - 28 Mar | ML-8 quantisation + ONNX latency study; CV-5 segmentation | HW-8 PCB v1 designed and ordered; HW-9 FOC started on a dev board | VS-? | Website v2: results page across all robots |

Month 6 onward: continue from Part B of `DELIVERABLES.md` and `HARDWARE_BUILD_ROADMAP.md`,
choosing the next items with the concept-density matrix.

The holiday sprint (21 Dec - 3 Jan) is planned at half capacity.

---

## 4. Bi-weekly sprints (first four)

| Sprint | Dates | Sprint goal | Main items |
|---|---|---|---|
| **S1** | 12-25 Oct | Class MVP functionally complete (2-week plan) | Shared setup; R1, R2, R3 in parallel; integrate; report draft. Board + website skeleton. Order HW-1/HW-2 parts. |
| **S2** | 26 Oct - 8 Nov | Class MVP polished and presented; hardware bench ready | Buffer for anything left from S1 (this is the 4-week plan's second half); report polish; code-quality pass on your scripts; HW-1 safety checklist + e-stop test; HW-2 blink, UART, debugger |
| **S3** | 9-22 Nov | CI running on R-SIM; first closed loop on hardware | SW-1 CI (lint, build, test); SW-2 environment pinned; HW-2 done; HW-3 wiring + encoder reading |
| **S4** | 23 Nov - 6 Dec | Tests protecting R-SIM; DC motor step response | SW-3 characterisation tests; ML-1 seeds/configs/logging; HW-3 1 kHz loop + step-response plot |

---

## 5. Weekly plan (first four weeks)

| Week | Dates | Main deliverables | Small deliverables |
|---|---|---|---|
| W1 | 12-18 Oct | Shared setup gate passed; R1 calibration captured; R2 dataset script producing checked images | Project board configured; issue templates in use |
| W2 | 19-25 Oct | R1 table; R2 trained with mAP; R3 working on GT then YOLO boxes; report draft | Website skeleton deployed; HW parts ordered |
| W3 | 26 Oct - 1 Nov | Report polished; figures final; code-quality pass (ruff, tests on maths functions, README commands) | HW-1 bench and e-stop set up |
| W4 | 2-8 Nov | Present class MVP; tag release `class-mvp-v1.0` | HW-2 blink + UART + breakpoints; devlog post on the class results |

---

## 6. Daily plan (Sprint 1: 12-25 October)

Maps the class MVP's 2-week schedule onto real dates. "Small" items fill the gaps.

| Date | Main task | Small task |
|---|---|---|
| Mon 12 Oct | Shared setup: sim headless, camera topics, intrinsics read | Create project board + fields (section 7) |
| Tue 13 Oct | Shared setup: GT pose logging, preset arm poses; **day-2 gate** | Add issues for R1-R4 from the acceptance checklists |
| Wed 14 Oct | R1: checkerboard in world; capture script | R2: decide 2-3 object classes |
| Thu 15 Oct | R2: randomiser + projected labels + YOLO export; check 50 images | R1: start capture of ~15 poses |
| Fri 16 Oct | R1: solve intrinsics + hand-eye (2 methods) | Devlog #1; board tidy |
| Sat 17 Oct | R2: start full capture running in background | R3: depth crop from GT boxes |
| Sun 18 Oct | Buffer / rest | — |
| Mon 19 Oct | R1: compare to URDF, table; **day-6 gate** | Colab notebook dry run on a few images |
| Tue 20 Oct | R2: train on Colab; R3: plane removal + PCA init | Website skeleton |
| Wed 21 Oct | R2: evaluate mAP; overlay images; **day-8 gate** | Order HW parts |
| Thu 22 Oct | R3: ICP + metrics on GT boxes | — |
| Fri 23 Oct | R3: swap in YOLO boxes; **day-11 gate** | Devlog #2 |
| Sat 24 Oct | Integrate calibrated transform into R3; rerun | Report outline |
| Sun 25 Oct | Report draft: three tables, limitations | Sprint 1 review note |

If a gate fails, the remaining days shift into Sprint 2 (the 4-week plan). Nothing else
in Sprint 1 takes priority over the class MVP.

---

## 7. GitHub project board setup

One **user-level** project (so it can hold issues from several repos: R-SIM, R-HW,
R-VS, website). Make it public if you want it to show completed work.

### Fields

| Field | Type | Values |
|---|---|---|
| Status | Single select | Backlog, Ready, In progress, Review, Done |
| Robot | Single select | R-SIM, R-HW, R-VS, Portfolio |
| Track | Single select | CV, ML, EMB/HW, SW, Report, Website |
| Tier | Single select | Class MVP, MVP+, Advanced, Stretch |
| Deliverable ID | Text | e.g. `R2`, `HW-3`, `ML-6` |
| Sprint | Iteration | 2-week iterations starting 12 Oct 2026 |
| Size | Single select | S (≤2 h), M (≤4 h), L (split it) |
| Evidence | Text (URL) | PR, plot, video, test result |

Milestones (M1-M6) live in each repo and match the dates in section 3.

### Views

| View | Layout | Filter / group | Purpose |
|---|---|---|---|
| Sprint board | Board | Current iteration, grouped by Status | Daily work |
| Roadmap | Roadmap | Grouped by Robot, by Sprint | Monthly picture |
| By robot | Table | Grouped by Robot then Track | Concept coverage at a glance |
| Shipped | Table | Status = Done, Evidence not empty | The "what was accomplished" view |
| Class MVP | Table | Tier = Class MVP | Teacher-facing progress |

### Automation (built into GitHub Projects)

- Auto-add new issues and PRs from the robot repos.
- Item closed or PR merged -> Status = Done.
- PR opened that links an issue -> Status = Review.

### Labels (per repo)

`track:cv`, `track:ml`, `track:emb`, `track:sw`, `type:deliverable`, `type:experiment`,
`type:bug`, `tier:class-mvp`, `tier:mvp+`, `tier:advanced`, `tier:stretch`, `blocked`.

### Issue templates

This repo includes issue forms in `.github/ISSUE_TEMPLATE/`:
- **Deliverable**: ID, robot, track, acceptance criteria, evidence.
- **Experiment**: hypothesis, setup, metric, result, conclusion.
- **Bug**: steps, expected, actual, environment.

Copy them into the other robot repos so every board item has the same shape.

---

## 8. Portfolio website

Static site on GitHub Pages (Astro, Hugo, Jekyll or MkDocs all work).

| Page | Content | Updated |
|---|---|---|
| Home | One line on what you build; three robot cards with current status | Monthly |
| Robot pages (one per robot) | Goal, architecture diagram, results table, videos, link to repo and board | At each milestone |
| Results | Every metric you have published, each linking to the script that produced it | At each milestone |
| Devlog | Short weekly or bi-weekly entries copied from `docs/devlog/` | Weekly or per sprint |
| About | Resume PDF, contact, skills grouped by concept-density matrix rows | As needed |

Content flow: issue evidence -> devlog entry (weekly) -> robot page update (monthly).
Write once in the repo; the website pulls or copies from it.

---

## 9. Review checklist per level

**Daily:** committed? issue comment written?
**Weekly (Fri):** issues closed with evidence? devlog entry? board current?
**Sprint end:** sprint goal met? review note written? next sprint's goal chosen?
**Milestone end:** release tagged? demo recorded? website robot page updated? matrix updated?
