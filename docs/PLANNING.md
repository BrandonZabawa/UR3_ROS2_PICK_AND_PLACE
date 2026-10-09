# Planning cadence: full-time solo-dev mode

Monthly, bi-weekly, weekly and daily plan for running several robot projects as a
full-time job (about 55-60 hours a week, 10-12 hours on weekdays), until output is
predictable enough to scale down to a sustainable load.

Calendar starts **Monday 12 October 2026**. Sprints are two weeks; milestones close
every second sprint (four weeks).

## Ground rules

| Rule | Value |
|---|---|
| Work hours | Mon-Fri 10-12 h, Saturday 6-8 h, Sunday off except a 1 h weekly review |
| Weekly output | **At least 1 deliverable done per week** (done = closed with evidence) |
| Sprint output | **At least 2 deliverables per sprint**, more as skill and familiarity grow (target 3-4 at this workload) |
| Classes | Not scheduled here. You plan them. Class concepts feed the robots (see "Class-to-robot hook" below). |
| Proof of work | Every closed item has evidence, estimated vs actual hours, and a "what I learned" note |
| Essentials | Sleep, exercise, meals and people are fixed blocks in the day plan, not leftovers |

## Workload phases and scale-down triggers

| Phase | Weekly hours | Ends when |
|---|---|---|
| **1. Ramp** | 55-60 | Scale-down triggers met over 3 consecutive sprints (earliest end of M3) |
| **2. Stabilise** | 45-50 | Triggers still met over 3 more sprints at the lower hours |
| **3. Sustainable** | ~40 | Ongoing |

**Scale-down triggers** (check at each sprint review; all must hold):
1. At least 80% of the deliverables committed to in the sprint were closed with evidence.
2. Actual hours within ±25% of the estimate for at least 70% of closed items.
3. No item carried over for more than one sprint.
4. The next two sprints' backlog is already written and sized.

**Cut-scope triggers** (if any holds, remove scope; do not add hours):
- Two sprints in a row below the 2-deliverable minimum.
- Sleep or exercise blocks skipped on more than 2 days in a week.
- The same item blocked for more than a week with no plan to unblock it.

---

## 1. The robots and what each one carries

| Robot | Role | Tracks it carries | Share of hours (Phase 1) |
|---|---|---|---|
| **R-SIM: UR3 suite (this repo)** | Software / vision / ML flagship | CV, DL/ML, ROS 2, MoveIt, software engineering, FANUC as a second arm config | ~35% (~20 h) |
| **R-HW: "DUM-E" custom arm (new repo)** | Embedded / hardware flagship | Firmware, PCB, motor control, CAN, RTOS, system identification, ros2_control hardware interface | ~35% (~20 h) |
| **R-VS: Viable Solutions arm** | Industrial / integration | Fill in from that project (`VS-*`) | ~10-15% |
| **R-CLUB: club robots** | Team contributions | Fill in from the club's needs (`CLUB-*`) | ~5-10% |
| **Portfolio + tracker + learning** | Evidence and reading | Devlog, website, datasheets, papers | ~5-10% |

Each monthly milestone on R-SIM and R-HW must exercise **at least two tracks** (for
example firmware + control + modelling), so no month produces a single-skill result.
The robots feed each other:
- DUM-E's measured motor data improves the UR3 simulator (system identification).
- The UR3 suite's calibration and pose code later runs on DUM-E's camera.
- The arm-config layer (SW-6) makes DUM-E and FANUC selectable arms in the suite.

### Concept-density matrix

`●` core, `○` secondary, `?` fill in.

| Concept | R-SIM | R-HW | R-VS | R-CLUB |
|---|---|---|---|---|
| Camera + hand-eye calibration | ● | ○ | ? | ? |
| Detection, datasets, mAP | ● |  | ? | ? |
| 6-DoF pose, point clouds, ICP | ● | ○ | ? | ? |
| Training, ablations, quantisation, deployment | ● | ○ | ? | ? |
| Imitation / reinforcement learning | ○ |  | ? | ? |
| Motion planning (MoveIt, MTC) | ● | ○ | ? | ? |
| ros2_control (controllers + hardware interface) | ○ | ● | ? | ? |
| Firmware: timers, PWM, ADC/DMA, interrupts |  | ● | ? | ? |
| Buses: CAN, UART, SPI |  | ● | ? | ? |
| Motor control: PID, FOC |  | ● | ? | ? |
| RTOS, timing, WCET |  | ● | ? | ? |
| PCB design and bring-up |  | ● | ? | ? |
| Mechanical design (printed gearboxes, tolerances) |  | ● | ? | ? |
| Safety: e-stop, watchdog, faults | ○ | ● | ? | ? |
| System identification, sim-to-real | ● | ● | ? | ? |
| CI, tests, code quality, docs | ● | ● | ? | ? |

### Class-to-robot hook

Classes are yours to plan. One rule connects them to this plan: when a class covers a
concept in the matrix, open a small issue (size S or M) that applies it to one robot.
These count toward the weekly deliverable minimum like any other item.

---

## 2. DUM-E on a budget

Commercial open arms such as PAROL6 are out of budget, so DUM-E is built in stages from
low-cost parts, using open designs as free references. You keep the firmware learning
because you write every layer yourself.

| Stage | Hardware | What it teaches | Cost pressure |
|---|---|---|---|
| A. One joint | Dev board (e.g. STM32 Nucleo with built-in debugger), brushed DC gearmotor with encoder, small H-bridge, bench supply | PWM, encoders, ADC, PID, CAN, ros2_control | Lowest; reuse everything later |
| B. FOC joint | Small gimbal BLDC, low-cost FOC driver board, magnetic encoder | Field-oriented control, current sensing, calibration | Low |
| C. 3-DoF desktop arm | Stage A or B joints, 3D-printed links and reductions (makerspace/library printers or a print service) | Mechanics, multi-joint bus, kinematics, gravity compensation | Moderate; spread over months |
| D. Own boards | KiCad board replacing the dev board + driver | PCB design and bring-up | Moderate; cheap prototype fab services |
| E. Camera on DUM-E | Low-cost USB/depth camera | Runs R-SIM's calibration and pose code on real hardware | Low-moderate |

Ways to stay close to open-source arms without owning one:
- Read PAROL6, AR4 and Moveo design files and firmware as references (free; check each licence).
- Contribute where cheap hardware is enough: SimpleFOC (a gimbal motor and driver board),
  ros2_control, MoveIt docs and examples, or software-only issues on the arm projects.
- Simulate an open arm's URDF in the UR3 suite once SW-6 makes arms selectable.

Check current prices before ordering; this plan names no prices.

---

## 3. Cadence and proof of work

| Level | Length | Minimum output | Recorded in |
|---|---|---|---|
| **Milestone** | 4 weeks (2 sprints) | Per robot: a tagged release, demo video or GIF, results plot/table | GitHub milestone + release; website robot page |
| **Sprint** | 2 weeks | ≥2 deliverables done (target 3-4); sprint review note with velocity | Board iteration; `docs/devlog/` |
| **Week** | 7 days | ≥1 deliverable done; devlog entry | Board; devlog |
| **Day** | one work day | A commit or PR on the main task; an issue log comment | Commits; issue comments |

**Definition of done:** merged PR or test result, evidence link, estimated vs actual
hours, and a "what I learned" note on the issue. No evidence, not done.

**Velocity:** at each sprint review, record deliverables done, hours estimated vs actual,
and items carried over. This is the data the scale-down triggers use.

---

## 4. Daily template (weekdays, ~10.5-11.5 h of work)

| Time | Block | Notes |
|---|---|---|
| 07:00 | Wake | 8 h sleep window ends |
| 07:15-08:00 | Exercise | Fixed |
| 08:00-08:30 | Breakfast, read the day's plan | |
| 08:30-12:30 | **Deep block 1 (4 h):** hardest task of the day | Usually R-HW or R-SIM main deliverable |
| 12:30-13:15 | Lunch, away from the desk | |
| 13:15-17:15 | **Deep block 2 (4 h):** second robot's main task | Alternate robots from block 1 |
| 17:15-17:45 | Walk / break | |
| 17:45-20:15 | **Block 3 (2.5 h):** tests, docs, tracker updates, R-VS / R-CLUB items, datasheets | Shallower work |
| 20:15-21:30 | Dinner and people | Fixed |
| 21:30-22:30 | Optional block 4 (1 h) **or** reading/gaming | Only when ahead of plan |
| 22:30-23:00 | Wind down; no screens if possible | |
| 23:00 | Sleep | |

**Saturday (6-8 h):** long uninterrupted bench sessions (soldering, bring-up, mechanical
assembly) and anything that needs hours of setup.
**Sunday:** off. One hour for the weekly review (section 8).

Daily rule: each deep block targets one issue; tasks bigger than ~4 h are split before
they start. End the day with a one-line comment on each touched issue: done, next, blocked.

---

## 5. Monthly milestones (Phase 1 and first half of Phase 2)

| Milestone | Dates | R-SIM (UR3 suite) | R-HW (DUM-E) | R-VS / R-CLUB | Portfolio |
|---|---|---|---|---|---|
| **M1** | 12 Oct - 8 Nov 2026 | SW-1 CI, SW-2 pinned environment, SW-3 characterisation tests, SW-4 logging cleanup, ML-1 experiment hygiene | HW-1 bench + safety, HW-2 dev-board bring-up, EMB-1 portable servo core with host tests, HW-3 started | VS-? / CLUB-? | Board live; website v1; devlog weekly |
| **M2** | 9 Nov - 6 Dec | SW-5 remove duplicates, SW-6 per-arm config, SW-9 logic split from nodes, ML-2 own mAP, CV-3 point clouds | HW-3 closed-loop DC joint with step-response plot; EMB-2 motor model compared to it; HW-4 CAN node | VS-? / CLUB-? | Post: "Sim vs real joint" |
| **M3** | 7 Dec - 3 Jan 2027 | SW-7 FANUC selectable in sim, SW-8 lifecycle nodes, ML-3 dataset audit, ML-4 CNN from scratch | HW-5 ros2_control drives the real joint; HW-6 safety + telemetry; HW-7 write-up -> **hardware MVP v1.0** | VS-? / CLUB-? | Demo video; first scale-down check |
| **M4** | 4 Jan - 31 Jan | CV-2 stereo depth, CV-4 PnP pose, ML-6 YOLO ablations | DUM-E stage C mechanical design; HW-10 printed reduction; HW-11 system identification | VS-? / CLUB-? | Post: "DUM-E design" |
| **M5** | 1 Feb - 28 Feb | CV-5 segmentation, CV-7 visual servoing, ML-8 quantisation + ONNX latency | HW-9 FOC joint (stage B); HW-12 three joints on one CAN bus; HW-13 RTOS + jitter measurement | VS-? / CLUB-? | Release: DUM-E v0.2 (3 joints moving) |
| **M6** | 1 Mar - 28 Mar | CV-9 learned pose or ML-11 imitation learning; repo restructure per `REPO_STRUCTURE.md` | HW-8 PCB v1 designed and ordered; HW-16 kinematics + repeatability; HW-17 camera on DUM-E running R-SIM calibration | VS-? / CLUB-? | Website v2: results across all robots |

Hardware lead times (parts, PCBs) can slip R-HW items; keep a software-only R-HW task
ready (simulation, firmware tests, docs) for waiting periods.

The holiday sprint (21 Dec - 3 Jan) is planned at half capacity.

---

## 6. Bi-weekly sprints (first six, Phase 1)

| Sprint | Dates | Sprint goal | Committed deliverables (≥2, target 3-4) |
|---|---|---|---|
| **S1** | 12-25 Oct | Foundations: CI and a working bench | SW-1 CI · SW-2 pinned env · HW-1 bench + e-stop · board + website skeleton |
| **S2** | 26 Oct - 8 Nov | Tests on R-SIM, firmware on a board | SW-3 characterisation tests · SW-4 logging cleanup · HW-2 bring-up · EMB-1 servo core |
| **S3** | 9-22 Nov | First closed loop on real hardware | HW-3 DC joint loop · SW-5 de-duplication · ML-1 experiment hygiene |
| **S4** | 23 Nov - 6 Dec | Sim and real agree; arms become config | EMB-2 motor model vs HW-3 data · SW-6 per-arm config · HW-4 CAN node |
| **S5** | 7-20 Dec | ROS 2 drives your own joint | HW-5 ros2_control interface · SW-9 logic split · ML-2 own mAP |
| **S6** | 21 Dec - 3 Jan | Hardware MVP release (half capacity) | HW-6 safety + telemetry · HW-7 write-up · first scale-down check |

---

## 7. Weekly plan (first four weeks)

| Week | Dates | Deliverables closed (≥1) | Also in progress |
|---|---|---|---|
| W1 | 12-18 Oct | SW-1 CI running on PRs | SW-2 environment; HW-1 bench set up, parts ordered; board configured |
| W2 | 19-25 Oct | SW-2 pinned environment; HW-1 bench + e-stop tested | Website skeleton; HW-2 toolchain |
| W3 | 26 Oct - 1 Nov | HW-2 dev-board bring-up (debugger, UART, timer IRQ) | SW-3 characterisation tests; EMB-1 started |
| W4 | 2-8 Nov | SW-3 tests; EMB-1 servo core with host tests | SW-4 logging cleanup; HW-3 wiring |

## 8. Day-by-day (week 1: 12-18 October)

| Date | Deep block 1 (4 h) | Deep block 2 (4 h) | Block 3 (2.5 h) |
|---|---|---|---|
| Mon 12 Oct | SW-1: lint config (ruff, clang-format) | HW-1: list bench parts, safety checklist draft | Create board, fields, views; issues for S1 |
| Tue 13 Oct | SW-1: CI workflow (lint + colcon build) | HW-1: e-stop wiring plan; order parts | VS-? / CLUB-? |
| Wed 14 Oct | SW-1: fix lint/build failures; CI green | SW-2: decide ROS + Gazebo pairing; document it | Devlog draft |
| Thu 15 Oct | SW-2: reproduce install from scratch (container) | HW-2: toolchain install; blink on the dev board | VS-? / CLUB-? |
| Fri 16 Oct | SW-2: fix README/INSTALL contradictions | HW-2: debugger breakpoints working | Close W1 items with evidence; devlog #1 |
| Sat 17 Oct | Bench session: set up workspace, test supply current limit (6 h) | | |
| Sun 18 Oct | Off. Weekly review (1 h). | | |

---

## 9. Reviews

| When | Time | Checks |
|---|---|---|
| Daily, end of day | 10 min | Commits pushed; issue comments written; tomorrow's two main tasks chosen |
| Weekly, Sunday | 1 h | ≥1 deliverable closed with evidence; devlog entry; essentials kept (sleep, exercise, people) |
| Sprint end | 1.5 h | ≥2 deliverables; velocity recorded; scale-down and cut-scope triggers checked; next sprint committed |
| Milestone end | 2-3 h | Releases tagged; demo recorded; website updated; concept matrix updated |

---

## 10. GitHub project board (proof of work)

One **user-level** project so it holds issues from every repo (UR3 suite, DUM-E,
Viable Solutions, club, website). Make it public if it should show completed work.

### Fields

| Field | Type | Values |
|---|---|---|
| Status | Single select | Backlog, Ready, In progress, Review, Done |
| Robot | Single select | R-SIM, R-HW, R-VS, R-CLUB, Portfolio |
| Track | Single select | CV, ML, EMB/HW, SW, Mechanical, Website |
| Tier | Single select | MVP+, Advanced, Stretch |
| Deliverable ID | Text | e.g. `SW-1`, `HW-3`, `ML-6` |
| Sprint | Iteration | 2-week iterations starting 12 Oct 2026 |
| Size | Single select | S (≤2 h), M (≤4 h), L (split it) |
| Est. hours | Number | Set when planned |
| Actual hours | Number | Set when closed |
| Evidence | Text (URL) | PR, plot, video, test output |

### Views

| View | Layout | Filter / group | Purpose |
|---|---|---|---|
| Today | Board | Status = In progress | Daily work |
| Sprint | Board | Current iteration, by Status | Sprint progress |
| Roadmap | Roadmap | By Robot, by Sprint | Monthly picture |
| By robot | Table | By Robot then Track | Concept coverage |
| Shipped | Table | Status = Done, Evidence set, sorted by close date | Proof of work |
| Velocity | Table | Group by Sprint, sum Est. and Actual hours | Scale-down data |

### Automation, labels, templates

- Built-in workflows: auto-add issues/PRs from all repos; closed or merged -> Done; PR linked -> Review.
- Labels: `track:cv`, `track:ml`, `track:emb`, `track:sw`, `track:mech`, `type:deliverable`,
  `type:experiment`, `type:bug`, `tier:mvp+`, `tier:advanced`, `tier:stretch`, `blocked`.
- Issue forms in `.github/ISSUE_TEMPLATE/` (Deliverable, Experiment, Bug) include estimated
  hours, actual hours, evidence and "what I learned". Copy them into the other repos.

---

## 11. Portfolio website

Static site on GitHub Pages (Astro, Hugo, Jekyll or MkDocs).

| Page | Content | Updated |
|---|---|---|
| Home | One line on what you build; a card per robot with current status | Monthly |
| Robot pages | Goal, architecture, results table, videos, links to repo and board | Each milestone |
| Results | Every published metric, each linking to the script that produced it | Each milestone |
| Devlog | Weekly entries copied from `docs/devlog/` | Weekly |
| About | Resume PDF, contact, skills grouped by the concept matrix | As needed |

Content flow: issue evidence -> weekly devlog -> robot page at each milestone. Write once
in the repo; the site copies from it.
