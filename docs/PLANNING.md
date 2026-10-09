# Planning cadence: full-time solo-dev mode

Monthly, bi-weekly, weekly and daily plan for running several robot projects as a
full-time job, until output is predictable enough to scale down to a sustainable load.
Applies to every robot you build; add new robots with the checklist in section 2.

Calendar starts **Monday 12 October 2026**. Sprints are two weeks; milestones close
every second sprint (four weeks). Hardware purchasing decisions follow
[`BUILD_VS_BUY.md`](BUILD_VS_BUY.md).

## Ground rules

| Rule | Value |
|---|---|
| Sleep | **9 h**, fixed (22:30-07:30). This leaves 15 waking hours. |
| Standard work day | **10 h** Mon-Fri. 11 h allowed on at most 2 days a week by dropping that day's hobby block. 12 h days are not planned: with 9 h sleep they only fit by cutting exercise, meals or people. |
| Saturday | 7 h, mostly long bench or build sessions |
| Sunday | Off, except a 1 h weekly review |
| Weekly total | ~57 h (50 weekday + 7 Saturday), up to ~59 h with two 11 h days |
| Weekly output | **At least 1 deliverable done per week** (done = closed with evidence) |
| Sprint output | **At least 2 deliverables per sprint**, more as skill and familiarity grow (target 3-4) |
| Classes | Not scheduled here; you plan them. See "Class-to-robot hook". |
| Proof of work | Every closed item has evidence, estimated vs actual hours, and a "what I learned" note |

## Workload phases and scale-down triggers

| Phase | Weekly hours | Ends when |
|---|---|---|
| **1. Ramp** | ~57 | Scale-down triggers met over 3 consecutive sprints (earliest end of M3) |
| **2. Stabilise** | 45-50 | Triggers still met over 3 more sprints at the lower hours |
| **3. Sustainable** | ~40 | Ongoing |

**Scale-down triggers** (check at each sprint review; all must hold):
1. At least 80% of the deliverables committed to in the sprint were closed with evidence.
2. Actual hours within ±25% of the estimate for at least 70% of closed items.
3. No item carried over for more than one sprint.
4. The next two sprints' backlog is already written and sized.

**Cut-scope triggers** (if any holds, remove scope; do not add hours):
- Two sprints in a row below the 2-deliverable minimum.
- Sleep, exercise or people blocks skipped on more than 2 days in a week.
- The same item blocked for more than a week with no plan to unblock it.

---

## 1. Daily template (weekdays, 10 h of work)

| Time | Block | Length |
|---|---|---|
| 07:30 | Wake (9 h sleep ends) | |
| 07:45-08:30 | Exercise | 45 min |
| 08:30-09:00 | Breakfast; read the day's plan | 30 min |
| 09:00-13:00 | **Deep block 1: hardware primary** (section 3) | 4 h |
| 13:00-13:45 | Lunch, away from the desk | 45 min |
| 13:45-17:45 | **Deep block 2: software primary** | 4 h |
| 17:45-18:00 | Short break / walk | 15 min |
| 18:00-20:00 | **Block 3: secondaries** (other robots, club, tests, docs, tracker, datasheets) | 2 h |
| 20:00-21:15 | Dinner and people | 1 h 15 min |
| 21:15-22:00 | Reading or gaming | 45 min |
| 22:00-22:30 | Wind down | 30 min |
| 22:30 | Sleep | 9 h |

**11 h day (max 2 per week):** extend block 3 to 21:00, move dinner to 21:00-22:00, drop
reading/gaming that day.

**Saturday (7 h):** 09:00-13:00 and 14:00-17:00, long hardware sessions (soldering,
bring-up, assembly, test drives) for the hardware primary.
**Sunday:** off. One hour for the weekly review (section 9).

Daily rules: each deep block targets one issue; tasks bigger than ~4 h are split before
they start; end the day with a one-line comment on each touched issue (done, next, blocked).

---

## 2. Robot registry

| ID | Robot | Role | Main tracks |
|---|---|---|---|
| **R-SIM** | UR3 suite (this repo) | Software / vision / ML flagship | CV, DL/ML, ROS 2, MoveIt, software engineering, FANUC config |
| **R-HW** | "DUM-E" custom arm | Embedded / electrical flagship (manipulation) | Firmware, PCB, motor control, CAN, RTOS, system ID |
| **R-AV** | Autonomous racecar | Autonomy flagship (mobile) | Perception, localisation, planning, control, sensor fusion, embedded I/O |
| **R-VS** | Viable Solutions arm | Industrial / integration | Fill in (`VS-*`) |
| **R-CLUB** | Club robots | Team contributions | Fill in (`CLUB-*`) |

### Adding a new robot

1. Give it an ID (`R-XXX`) and add it to the board's Robot field and the issue template dropdown.
2. Add a column to the concept-density matrix; aim for at least one concept no other robot covers well.
3. Write its staged path (like DUM-E's and R-AV's in section 4).
4. Run every subsystem through `BUILD_VS_BUY.md` before buying anything.
5. Create its repo from the skeleton in `REPO_STRUCTURE.md`.
6. Schedule it as a secondary first; it becomes a primary only through the rotation in section 3.

### Concept-density matrix

`●` core, `○` secondary, `?` fill in.

| Concept | R-SIM | R-HW | R-AV | R-VS | R-CLUB |
|---|---|---|---|---|---|
| Camera calibration, hand-eye / extrinsics | ● | ○ | ● | ? | ? |
| Detection, datasets, mAP | ● |  | ● | ? | ? |
| 6-DoF pose, point clouds, ICP | ● | ○ | ○ | ? | ? |
| Training, ablations, quantisation, edge deployment | ● | ○ | ● | ? | ? |
| Imitation / reinforcement learning | ○ |  | ● | ? | ? |
| Localisation, SLAM, sensor fusion |  | ○ | ● | ? | ? |
| Motion planning | ● | ○ | ● | ? | ? |
| Control (PID, MPC, FOC) |  | ● | ● | ? | ? |
| ros2_control / hardware interfaces | ○ | ● | ○ | ? | ? |
| Firmware: timers, PWM, ADC/DMA, interrupts |  | ● | ○ | ? | ? |
| Buses: CAN, UART, SPI, I2C |  | ● | ● | ? | ? |
| Power electronics, batteries, wiring harness |  | ● | ● | ? | ? |
| PCB design and bring-up |  | ● | ○ | ? | ? |
| Mechanical design |  | ● | ○ | ? | ? |
| Safety: e-stop, watchdog, faults | ○ | ● | ● | ? | ? |
| System identification, sim-to-real | ● | ● | ● | ? | ? |
| CI, tests, code quality, docs | ● | ● | ● | ? | ? |

### Class-to-robot hook

Classes are yours to plan. When a class covers a concept in the matrix, open a small issue
(size S or M) that applies it to one robot. It counts toward the weekly deliverable minimum.

---

## 3. Primaries, secondaries and rotation

There are more robots than deep blocks, so each milestone has:
- **Hardware primary:** gets deep block 1 every weekday plus Saturday (~27 h/week).
- **Software primary:** gets deep block 2 every weekday (~20 h/week).
- **Secondaries:** share block 3 (~10 h/week) with tracker, devlog and website work.

Maximum two primaries at a time. Rotate per milestone, not per day; switching costs are real.
Adding R-AV means the earlier DUM-E dates move later; that is the trade-off of a third
active robot.

| Milestone | Hardware primary | Software primary | Secondaries |
|---|---|---|---|
| M1 | R-HW (DUM-E) | R-SIM | R-AV (sim set-up), R-VS, R-CLUB |
| M2 | R-HW (DUM-E) | R-AV (simulation stack) | R-SIM, R-VS, R-CLUB |
| M3 | R-AV (car bring-up) | R-SIM | R-HW, R-VS, R-CLUB |
| M4 | R-HW (DUM-E) | R-AV (real car) | R-SIM, R-VS, R-CLUB |
| M5 | R-AV (own electronics) | R-SIM | R-HW, R-VS, R-CLUB |
| M6 | R-HW (DUM-E) | R-AV (advanced autonomy) | R-SIM, R-VS, R-CLUB |

---

## 4. Staged hardware paths

Purchasing at each stage follows `BUILD_VS_BUY.md`. No prices are given here; check
current prices before ordering.

### R-HW: DUM-E on a budget

| Stage | Hardware | What it teaches |
|---|---|---|
| A. One joint | Dev board (e.g. STM32 Nucleo with built-in debugger), DC gearmotor with encoder, H-bridge module, bench supply | PWM, encoders, ADC, PID, CAN, ros2_control |
| B. FOC joint | Gimbal BLDC, low-cost FOC driver board, magnetic encoder | Field-oriented control, current sensing, calibration |
| C. 3-DoF arm | Stage A/B joints, 3D-printed links and reductions (makerspace or print service) | Mechanics, multi-joint bus, kinematics, gravity compensation |
| D. Own boards | KiCad board replacing dev board + driver | PCB design and bring-up |
| E. Camera | Low-cost USB or depth camera | R-SIM calibration and pose code on real hardware |

Staying close to open arms like PAROL6 without owning one: study their published files
(free; check licences), contribute where cheap hardware is enough (SimpleFOC, ros2_control,
MoveIt), or simulate an open arm's URDF in R-SIM once arms are selectable (SW-6).

### R-AV: autonomous racecar

The 1/10-scale autonomous racing community (F1TENTH) publishes open build guides and a
simulator; check their current docs before buying.

| Stage | Hardware | What it teaches |
|---|---|---|
| A. Simulation | None. A racing simulator (e.g. the F1TENTH gym) or Gazebo with ROS 2 | Localisation, pure pursuit, raceline planning, lap-time metrics |
| B. Bought platform | Assembled RC chassis; an ESC with open firmware (VESC-based); single-board computer; 2D lidar or camera; IMU breakout | Bring-up, ROS 2 drivers, teleop, real localisation |
| C. Own I/O electronics | Your MCU board for wheel encoders, IMU, servo/ESC command and a watchdog, talking to the computer over UART or CAN | Firmware, buses, timing, safety cut-off |
| D. Own power board | Power distribution, fusing, battery monitoring, e-stop/kill switch | Power electronics, battery safety |
| E. Advanced autonomy | Same car | MPC, learned perception on the car's compute, imitation or RL policies, sim-to-real |

LiPo batteries can catch fire: use a fireproof charging bag, a balance charger, and never
charge unattended.

---

## 5. Monthly milestones

| Milestone | Dates | Hardware primary | Software primary | Secondaries (block 3) | Portfolio |
|---|---|---|---|---|---|
| **M1** | 12 Oct - 8 Nov 2026 | DUM-E: HW-1 bench + safety, HW-2 dev-board bring-up, EMB-1 servo core with host tests | R-SIM: SW-1 CI, SW-2 pinned env, SW-3 characterisation tests, SW-4 logging cleanup | R-AV stage A: simulator running with a car following a wall or centreline | Board live; website v1 |
| **M2** | 9 Nov - 6 Dec | DUM-E: HW-3 closed-loop joint + EMB-2 sim comparison; HW-4 CAN node | R-AV sim: localisation, pure pursuit on a raceline, lap-time and tracking-error metrics | R-SIM: SW-5 de-duplication; R-AV: stage B purchase decision per `BUILD_VS_BUY.md` | Post: "Sim vs real joint" |
| **M3** | 7 Dec - 3 Jan 2027 (half-capacity holiday sprint) | R-AV stage B: chassis, compute, ESC, lidar/IMU bring-up; teleop with e-stop | R-SIM: SW-6 per-arm config, SW-9 logic split, ML-1 experiment hygiene | DUM-E: HW-5 ros2_control design | First scale-down check |
| **M4** | 4 Jan - 31 Jan | DUM-E: HW-5 ros2_control drives the joint, HW-6 safety + telemetry, HW-7 write-up -> **DUM-E hardware MVP v1.0** | R-AV real car: localisation + pure pursuit at low speed; camera dataset for cone/lane detection | R-SIM: ML-2 own mAP | Demo video: DUM-E joint from ROS 2 |
| **M5** | 1 Feb - 28 Feb | R-AV stage C: own MCU I/O board (encoders, IMU, watchdog) on a dev board first | R-SIM: SW-7 FANUC selectable, ML-6 YOLO ablations | DUM-E: stage C mechanical design | Release: R-AV v0.1 (autonomous laps) |
| **M6** | 1 Mar - 28 Mar | DUM-E: HW-9 FOC joint, HW-12 joints on one CAN bus | R-AV: detector quantised and running on the car (ML-8); MPC or learned controller experiment | R-SIM: repo restructure per `REPO_STRUCTURE.md` | Website v2: results across robots |

Parts and PCB lead times can slip hardware items; keep a software-only task for the
hardware primary (simulation, firmware tests, docs) ready for waiting periods.

---

## 6. Bi-weekly sprints (first six)

| Sprint | Dates | Hardware primary | Software primary | Committed deliverables (≥2, target 3-4) |
|---|---|---|---|---|
| **S1** | 12-25 Oct | DUM-E | R-SIM | SW-1 CI · SW-2 pinned env · HW-1 bench + e-stop · board + website skeleton |
| **S2** | 26 Oct - 8 Nov | DUM-E | R-SIM | SW-3 tests · SW-4 logging · HW-2 bring-up · EMB-1 servo core · R-AV sim running |
| **S3** | 9-22 Nov | DUM-E | R-AV | HW-3 DC joint loop · R-AV localisation in sim · SW-5 de-duplication |
| **S4** | 23 Nov - 6 Dec | DUM-E | R-AV | EMB-2 model vs HW-3 data · HW-4 CAN node · R-AV pure pursuit + lap metrics · R-AV purchase decision |
| **S5** | 7-20 Dec | R-AV | R-SIM | R-AV chassis + compute bring-up · SW-6 per-arm config · ML-1 hygiene |
| **S6** | 21 Dec - 3 Jan | R-AV | R-SIM | R-AV teleop with e-stop · SW-9 logic split · scale-down check (half capacity) |

---

## 7. Weekly plan (first four weeks)

| Week | Dates | Deliverables closed (≥1) | Also in progress |
|---|---|---|---|
| W1 | 12-18 Oct | SW-1 CI running on PRs | HW-1 bench, parts ordered; SW-2; board configured |
| W2 | 19-25 Oct | SW-2 pinned environment; HW-1 bench + e-stop tested | Website skeleton; HW-2 toolchain; R-AV simulator install |
| W3 | 26 Oct - 1 Nov | HW-2 dev-board bring-up (debugger, UART, timer IRQ) | SW-3 tests; EMB-1 started |
| W4 | 2-8 Nov | SW-3 tests; EMB-1 servo core; R-AV car following a centreline in sim | SW-4 logging cleanup |

## 8. Day-by-day (week 1: 12-18 October)

| Date | Deep block 1, 09:00-13:00 (DUM-E) | Deep block 2, 13:45-17:45 (R-SIM) | Block 3, 18:00-20:00 (secondaries) |
|---|---|---|---|
| Mon 12 Oct | HW-1: bench parts list, safety checklist draft | SW-1: lint config (ruff, clang-format) | Create board, fields, views; S1 issues |
| Tue 13 Oct | HW-1: e-stop wiring plan; run parts through BUILD_VS_BUY; order | SW-1: CI workflow (lint + colcon build) | R-AV: pick simulator; read its docs |
| Wed 14 Oct | HW-2: toolchain install; blink on the dev board | SW-1: fix lint/build failures; CI green | VS-? / CLUB-? |
| Thu 15 Oct | HW-2: UART logging; debugger breakpoints | SW-2: decide ROS + Gazebo pairing; container build | R-AV: simulator install |
| Fri 16 Oct | HW-2: timer interrupt at a fixed rate; measure with logic analyzer if available | SW-2: fix README/INSTALL contradictions | Close W1 items with evidence; devlog #1 |
| Sat 17 Oct | Bench session (7 h): workspace, supply current-limit test, e-stop if parts arrived | | |
| Sun 18 Oct | Off. Weekly review (1 h). | | |

---

## 9. Reviews

| When | Time | Checks |
|---|---|---|
| Daily, end of block 3 | 10 min | Commits pushed; issue comments written; tomorrow's two deep-block tasks chosen |
| Weekly, Sunday | 1 h | ≥1 deliverable closed with evidence; devlog entry; essentials kept (sleep, exercise, people) |
| Sprint end | 1.5 h | ≥2 deliverables; velocity recorded; scale-down and cut-scope triggers checked; next sprint committed |
| Milestone end | 2-3 h | Releases tagged; demo recorded; website updated; matrix updated; next primaries confirmed |

### Cadence and proof of work

| Level | Length | Minimum output | Recorded in |
|---|---|---|---|
| Milestone | 4 weeks | Per primary robot: tagged release, demo video or GIF, results plot/table | GitHub milestone + release; website robot page |
| Sprint | 2 weeks | ≥2 deliverables done (target 3-4); review note with velocity | Board iteration; `docs/devlog/` |
| Week | 7 days | ≥1 deliverable done; devlog entry | Board; devlog |
| Day | one work day | A commit or PR on each deep-block task; issue log comments | Commits; issue comments |

**Definition of done:** merged PR or test result, evidence link, estimated vs actual hours,
and a "what I learned" note. No evidence, not done.

---

## 10. GitHub project board (proof of work)

One **user-level** project so it holds issues from every repo. Make it public if it should
show completed work.

### Fields

| Field | Type | Values |
|---|---|---|
| Status | Single select | Backlog, Ready, In progress, Review, Done |
| Robot | Single select | R-SIM, R-HW, R-AV, R-VS, R-CLUB, Portfolio (add new robots here) |
| Track | Single select | CV, ML, EMB/HW, SW, Mechanical, Website |
| Tier | Single select | MVP+, Advanced, Stretch |
| Deliverable ID | Text | e.g. `SW-1`, `HW-3`, `AV-2` |
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
  hours, actual hours, evidence and "what I learned". Copy them into each robot's repo.

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

Content flow: issue evidence -> weekly devlog -> robot page at each milestone.
