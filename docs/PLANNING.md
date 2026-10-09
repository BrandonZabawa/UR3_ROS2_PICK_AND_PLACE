# Planning cadence: full-time solo-dev mode

Monthly, bi-weekly, weekly and daily plan for running several robot projects as a
full-time job, until output is predictable enough to scale down to a sustainable load.
Applies to every robot you build; add new robots with the checklist in section 4.

Calendar starts **Monday 12 October 2026**. Sprints are two weeks; milestones close
every second sprint (four weeks). Hardware purchasing decisions follow
[`BUILD_VS_BUY.md`](BUILD_VS_BUY.md).

## Ground rules

| Rule | Value |
|---|---|
| Sleep | **9 h**, fixed (22:30-07:30). This leaves 15 waking hours. |
| Work window | **10 h** Mon-Fri. This is time at the desk or bench with distractions removed, attempting focus. It is **not** a promise of 10 h of deep work (see section 1). 11 h allowed on at most 2 days a week by dropping that day's hobby block. 12 h days are not planned: with 9 h sleep they only fit by cutting exercise, meals or people. |
| Saturday | 7 h window, mostly long bench or build sessions |
| Mode | **Bimodal**: Monday-Saturday are deep days; all shallow work goes into **one weekly shallow block** (section 2) |
| Sunday | **Weekly shallow block**, 3 h: the defined shallow list, weekly review, next week's plan. The rest of Sunday for people, exercise and hobbies. |
| Weekly window | ~60 h (50 weekday + 7 Saturday + 3 Sunday), up to ~62 h with two 11 h days |
| Capacity for planning | Based on **measured focused hours**, not window hours (section 1) |
| Weekly output | **At least 1 deliverable done per week** (done = closed with evidence) |
| Sprint output | **At least 2 deliverables per sprint**, more as skill and familiarity grow (target 3-4) |
| Classes | Not scheduled here; you plan them. See "Class-to-robot hook". |
| Proof of work | Every closed item has evidence, estimated vs actual hours, and a "what I learned" note |
| New ideas | Captured in one line in [`IDEAS_FOR_FUTURE_WORK.md`](IDEAS_FOR_FUTURE_WORK.md) and triaged in the shallow block; never acted on mid-session |
| Re-planning | Daily, at the end of window 3, when something goes off track; the deliverable date holds and the daily steps change |

## Workload phases and scale-down triggers

| Phase | Weekly hours | Ends when |
|---|---|---|
| **1. Ramp** | ~60 (window) | Scale-down triggers met over 3 consecutive sprints (earliest end of M3) |
| **2. Stabilise** | 45-50 | Triggers still met over 3 more sprints at the lower hours |
| **3. Sustainable** | ~40 | Triggers met over 3 sprints at ~40 h, and the class load allows the next step |
| **4. Long-term target** | ~20 project hours alongside classes (part-time or full-time) | Ongoing: projects stay on track and classes are passed |

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

## 1. Focus training and capacity

The work window is fixed; how much of it is real deep work is expected to start lower and
grow over months as focus is trained. Planning capacity follows deep-work ability.

The default mode is **bimodal**: six deep days a week, and shallow work pushed into one
weekly block (section 2). Inside the deep days, fixed windows give a rhythm so starting is
a habit rather than a decision. Over time the aim is to add **journalistic** ability on top:
dropping into depth within minutes whenever a gap appears, which also makes the remaining
context switches cheaper.

### Focus stages

| Stage | Typical months | Session length | Break | Target focused hours / weekday | Approach |
|---|---|---|---|---|---|
| **F1. Build the habit** | 0-2 | 25-45 min | 5-10 min | 4-5 | Bimodal; fixed windows and start ritual |
| **F2. Lengthen** | 2-4 | 60-90 min | 10-15 min | 5-6 | Bimodal; longer sessions |
| **F3. Sustain** | 4-8 | 90-120 min | 15-20 min | 6-7 | Bimodal; some flexible sessions |
| **F4. Journalistic** | 8-12+ | 2 h+ and short ad-hoc sessions | as needed | 7+ (stretch) | Bimodal + journalistic: enter depth within minutes, at any time in the window |

These targets are starting guesses. Your own log decides: if focused hours plateau for
three or more weeks despite good sleep and routine, treat the plateau as current capacity
and plan to it. Many experienced practitioners report about four hours of truly deep work a
day as a practical ceiling, so later-stage targets count focused work that includes
lighter-but-concentrated tasks (tests, debugging, docs).

**Move to the next stage** when, over 3 consecutive weeks:
1. At least 80% of planned focus sessions reached the stage's session length.
2. Median time from sitting down to working on the task is under 10 minutes (F3 and F4: under 5).
3. Weekday focused hours meet the stage target on at least 4 of 5 days.

**Step back a stage** for a week if sessions are being abandoned more often than completed;
a step back is a normal adjustment, not a failure.

### What happens in the window outside focus sessions

Breaks, setup, resume notes (below), and the end-of-day re-plan. Shallow tasks that come up
are written in the shallow inbox (section 2) and left for the weekly block. Reading needed
for the task at hand (a datasheet, a paper section) is part of the work, not shallow.

### Tasks run from shallow to deep

Each deliverable (and each epic above it) breaks into daily issues that range from shallow
to deep. Order them so the deep, risky issues start early in the deliverable's timeline,
leaving the shallow finishing work (docs, clean-up, evidence) for the end. When a deep issue
overruns, the deliverable date holds and the shallow steps compress or move.

### Capacity planning

- **Sprint commitment** = median focused hours per week (last 3 weeks) x 2 weeks x 0.8.
  The 0.8 leaves room for surprises.
- **M1 is a calibration month:** commit to the minimum (2 deliverables per sprint) and
  record focused hours from day one. From S3 onward, commitments use the measured numbers.
- Estimate issues in focused hours. Record actual focused hours on close.

### Removing obstacles (one thing at a time)

| Obstacle | Rule |
|---|---|
| Phone | Outside the room during windows 1 and 2; checked in breaks only |
| Notifications | Off on all devices during sessions; site blocker on during windows 1 and 2 |
| Messages, email | One 5-minute scan per day at lunch for urgent items only (school deadlines, safety, a parts problem). Everything else waits for the weekly shallow block. |
| Deciding what to do | Decided the evening before (end of window 3); one issue per session |
| Starting friction | Same start ritual each time: open the issue, write the session note (below), start timer |
| Context switching | One robot per window. Switches are allowed only by the stuck-triage and wait-time rules below, and every switch gets a resume note. |
| Getting stuck | Stuck-triage rule (below) |
| Waiting on runs | Wait-time rule (below) |
| Environment | Same desk set-up; bench tools put away from the coding desk |

### Stuck-triage rule

Being stuck is fine; the question is whether it blocks other work.

1. **Grappling or spinning?** Grappling means you are still forming and testing new
   hypotheses: keep going, this is where depth happens. Spinning means repeating attempts
   with no new ideas: go to step 2.
2. **After about 20 minutes of spinning,** write the problem state in the issue
   (what you tried, what you think is going on, the next hypothesis).
3. **Clear what you can finish quickly.** Do the tasks in the same window that can be
   finished, ideally on the same robot, to take them off the board.
4. **Take a break**, then give the hard problem a dedicated block of full concentration
   (for example 2 hours straight) to stay on schedule.
5. If the problem still blocks the deliverable after that block, it becomes the first task
   of the next window, and the day is re-planned around it.

### Wait-time rule

When a build, test, training run or data capture is running:
1. Write the pass/fail check before starting the run, so confirming it takes seconds.
2. Make long runs notify you when they finish.
3. Use the wait on the current hard problem (with a resume note for the run you left).
4. When the run finishes, check it against the written criterion, then return to the hard problem.

### Resume notes (preventing switching residue)

Before any switch, write three lines in the issue you are leaving: where you are, what you
were about to try, and what you expect to see. Re-entering starts by reading it. Research on
attention residue (Sophie Leroy) found that writing a ready-to-resume plan reduces the
residue a switch leaves behind; the notes also feed the session journal.

### Session journal (doubles as proof of work)

At the start of each session, write two lines in the issue: the goal of this session and
the first concrete step. At the end, write two lines: what got done, and the next step.
Over months this becomes the evidence trail on the board and the raw material for the devlog.

### Focus log

Log each session (date, robot, issue, planned length, actual length, time to start,
interruptions). A spreadsheet or a `docs/devlog/focus-log.csv` is enough. The weekly review
uses it for the stage criteria and the sprint commitment.

---

## 2. The weekly shallow block (Sunday, 3 h)

Bimodal mode keeps Monday-Saturday deep. Shallow work is captured during the week and done
in one block, so nothing important (especially anything that keeps you enrolled and on
track in school) gets forgotten.

### Shallow inbox

During the week, any shallow task that appears is written as one line in the shallow inbox
(a board view filtered on the `type:shallow` label, or a single pinned issue) and left
there. Only items flagged urgent in the daily 5-minute scan are handled before Sunday.

### Defined shallow list (done every Sunday)

| # | Item |
|---|---|
| 1 | Email and messages: reply, archive, or turn into an issue |
| 2 | School admin: deadlines, registration, forms, fees, advisor messages, grades check |
| 3 | Club admin: meeting notes, commitments, messages |
| 4 | Purchases: order parts (after `BUILD_VS_BUY.md`), track shipments, file receipts |
| 5 | Board grooming: close stale items, label new ones, size next week's issues |
| 6 | Triage `IDEAS_FOR_FUTURE_WORK.md`: promote to an issue, park, or drop |
| 7 | Devlog and website: publish the week's entry; update robot pages at milestones |
| 8 | Weekly review (section 11) and next week's plan |
| 9 | Calendar: confirm next week's fixed commitments (classes, meetings) |
| 10 | Anything else in the shallow inbox |

Items left over roll to next Sunday unless the daily scan flags them as urgent.

### Why Sunday holds it

Planning on Sunday keeps the six deep days free of decisions, and the rest of Sunday holds
the essentials (people, exercise, reading or gaming). If the focus log shows a different day
works better for the shallow block, move it; the rule is one block per week.

---

## 3. Daily template (weekdays, 10 h window)

| Time | Block | Length |
|---|---|---|
| 07:30 | Wake (9 h sleep ends) | |
| 07:45-08:30 | Exercise | 45 min |
| 08:30-09:00 | Breakfast; read the day's plan | 30 min |
| 09:00-13:00 | **Window 1: hardware primary** (section 5) | 4 h |
| 13:00-13:45 | Lunch, away from the desk; 5-minute urgent-only message scan | 45 min |
| 13:45-17:45 | **Window 2: software primary** | 4 h |
| 17:45-18:00 | Short break / walk | 15 min |
| 18:00-20:00 | **Window 3: secondaries** (other robots, club technical work, tests, docs) and the end-of-day re-plan (last 10 min) | 2 h |
| 20:00-21:15 | Dinner and people | 1 h 15 min |
| 21:15-22:00 | Reading or gaming | 45 min |
| 22:00-22:30 | Wind down | 30 min |
| 22:30 | Sleep | 9 h |

Inside windows 1 and 2, work in focus sessions of the current stage's length (section 1),
with breaks between them. Example at F1: four 45-minute sessions with 15-minute breaks per
window, so about 3 focused hours per 4-hour window.

**11 h day (max 2 per week):** extend window 3 to 21:00, move dinner to 21:00-22:00, drop
reading/gaming that day.

**Saturday (7 h):** 09:00-13:00 and 14:00-17:00, long hardware sessions (soldering,
bring-up, assembly, test drives) for the hardware primary.
**Sunday (weekly shallow block, 3 h):** 10:00-13:00, the defined shallow list in section 2,
including the weekly review and next week's plan. The rest of the day for people, exercise
and hobbies.

Daily rules: each window targets one issue; tasks bigger than ~4 focused hours are split
before they start; session notes at the start and end of each session and a resume note at
every switch (section 1); end the day by re-planning if anything went off track and choosing
tomorrow's window-1 and window-2 issues.

---

## 4. Robot registry

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
3. Write its staged path (like DUM-E's and R-AV's in section 6).
4. Run every subsystem through `BUILD_VS_BUY.md` before buying anything.
5. Create its repo from the skeleton in `REPO_STRUCTURE.md`.
6. Schedule it as a secondary first; it becomes a primary only through the rotation in section 5.

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

## 5. Primaries, secondaries and rotation

There are more robots than focus windows, so each milestone has:
- **Hardware primary:** window 1 every weekday plus Saturday (~27 h of window per week).
- **Software primary:** window 2 every weekday (~20 h of window per week).
- **Secondaries:** share window 3 (~10 h per week) with tracker, devlog and website work.

Focused hours are a fraction of these, set by the current focus stage.

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

## 6. Staged hardware paths

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

## 7. Monthly milestones

| Milestone | Dates | Hardware primary | Software primary | Secondaries (window 3) | Portfolio |
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

## 8. Bi-weekly sprints (first six)

| Sprint | Dates | Hardware primary | Software primary | Committed deliverables (≥2, target 3-4) |
|---|---|---|---|---|
| **S1** | 12-25 Oct | DUM-E | R-SIM | SW-1 CI · SW-2 pinned env · HW-1 bench + e-stop · board + website skeleton |
| **S2** | 26 Oct - 8 Nov | DUM-E | R-SIM | SW-3 tests · SW-4 logging · HW-2 bring-up · EMB-1 servo core · R-AV sim running |
| **S3** | 9-22 Nov | DUM-E | R-AV | HW-3 DC joint loop · R-AV localisation in sim · SW-5 de-duplication |
| **S4** | 23 Nov - 6 Dec | DUM-E | R-AV | EMB-2 model vs HW-3 data · HW-4 CAN node · R-AV pure pursuit + lap metrics · R-AV purchase decision |
| **S5** | 7-20 Dec | R-AV | R-SIM | R-AV chassis + compute bring-up · SW-6 per-arm config · ML-1 hygiene |
| **S6** | 21 Dec - 3 Jan | R-AV | R-SIM | R-AV teleop with e-stop · SW-9 logic split · scale-down check (half capacity) |

---

## 9. Weekly plan (first four weeks)

| Week | Dates | Deliverables closed (≥1) | Also in progress |
|---|---|---|---|
| W1 | 12-18 Oct | SW-1 CI running on PRs | HW-1 bench, parts ordered; SW-2; board configured |
| W2 | 19-25 Oct | SW-2 pinned environment; HW-1 bench + e-stop tested | Website skeleton; HW-2 toolchain; R-AV simulator install |
| W3 | 26 Oct - 1 Nov | HW-2 dev-board bring-up (debugger, UART, timer IRQ) | SW-3 tests; EMB-1 started |
| W4 | 2-8 Nov | SW-3 tests; EMB-1 servo core; R-AV car following a centreline in sim | SW-4 logging cleanup |

## 10. Day-by-day (week 1: 12-18 October)

| Date | Window 1, 09:00-13:00 (DUM-E) | Window 2, 13:45-17:45 (R-SIM) | Window 3, 18:00-20:00 (secondaries) |
|---|---|---|---|
| Mon 12 Oct | Set up focus log, site blocker, start ritual; HW-1: bench parts list, safety checklist draft | SW-1: lint config (ruff, clang-format) | Create board, fields, views; S1 issues |
| Tue 13 Oct | HW-1: e-stop wiring plan; run parts through BUILD_VS_BUY; order | SW-1: CI workflow (lint + colcon build) | R-AV: pick simulator; read its docs |
| Wed 14 Oct | HW-2: toolchain install; blink on the dev board | SW-1: fix lint/build failures; CI green | VS-? / CLUB-? |
| Thu 15 Oct | HW-2: UART logging; debugger breakpoints | SW-2: decide ROS + Gazebo pairing; container build | R-AV: simulator install |
| Fri 16 Oct | HW-2: timer interrupt at a fixed rate; measure with logic analyzer if available | SW-2: fix README/INSTALL contradictions | Close W1 items with evidence; devlog #1 |
| Sat 17 Oct | Bench session (7 h window): workspace, supply current-limit test, e-stop if parts arrived | | |
| Sun 18 Oct | Weekly shallow block (3 h): shallow list, focus-log review, plan W2 | | |

---

## 11. Reviews

| When | Time | Checks |
|---|---|---|
| Daily, end of window 3 | 10 min | Commits pushed; session notes written; focus log filled; tomorrow's two window tasks chosen |
| Weekly, Sunday (inside the shallow block) | 1 h | ≥1 deliverable closed with evidence; devlog entry; focused hours vs stage target; essentials kept (sleep, exercise, people) |
| Sprint end | 1.5 h | ≥2 deliverables; velocity and focused hours recorded; focus-stage, scale-down and cut-scope triggers checked; next sprint committed from measured capacity |
| Milestone end | 2-3 h | Releases tagged; demo recorded; website updated; matrix updated; next primaries confirmed |

### Cadence and proof of work

| Level | Length | Minimum output | Recorded in |
|---|---|---|---|
| Milestone | 4 weeks | Per primary robot: tagged release, demo video or GIF, results plot/table | GitHub milestone + release; website robot page |
| Sprint | 2 weeks | ≥2 deliverables done (target 3-4); review note with velocity | Board iteration; `docs/devlog/` |
| Week | 7 days | ≥1 deliverable done; devlog entry | Board; devlog |
| Day | one work day | A commit or PR on each window-1/2 task; session notes; focus log | Commits; issue comments; focus log |

**Definition of done:** merged PR or test result, evidence link, estimated vs actual hours,
and a "what I learned" note. No evidence, not done.

---

## 12. GitHub project board (proof of work)

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
| Est. focused hours | Number | Set when planned |
| Actual focused hours | Number | Set when closed |
| Evidence | Text (URL) | PR, plot, video, test output |

### Views

| View | Layout | Filter / group | Purpose |
|---|---|---|---|
| Today | Board | Status = In progress | Daily work |
| Sprint | Board | Current iteration, by Status | Sprint progress |
| Roadmap | Roadmap | By Robot, by Sprint | Monthly picture |
| By robot | Table | By Robot then Track | Concept coverage |
| Shipped | Table | Status = Done, Evidence set, sorted by close date | Proof of work |
| Velocity | Table | Group by Sprint, sum estimated and actual focused hours | Capacity and scale-down data |

### Automation, labels, templates

- Built-in workflows: auto-add issues/PRs from all repos; closed or merged -> Done; PR linked -> Review.
- Labels: `track:cv`, `track:ml`, `track:emb`, `track:sw`, `track:mech`, `type:deliverable`,
  `type:experiment`, `type:bug`, `type:shallow`, `type:idea`, `tier:mvp+`, `tier:advanced`,
  `tier:stretch`, `blocked`.
- Extra view: **Shallow inbox** (table, label `type:shallow`, open items), cleared every Sunday.
- Issue forms in `.github/ISSUE_TEMPLATE/` (Deliverable, Experiment, Bug) include estimated
  hours, actual hours, evidence and "what I learned". Copy them into each robot's repo.

---

## 13. Portfolio website

Static site on GitHub Pages (Astro, Hugo, Jekyll or MkDocs).

| Page | Content | Updated |
|---|---|---|
| Home | One line on what you build; a card per robot with current status | Monthly |
| Robot pages | Goal, architecture, results table, videos, links to repo and board | Each milestone |
| Results | Every published metric, each linking to the script that produced it | Each milestone |
| Devlog | Weekly entries copied from `docs/devlog/` | Weekly |
| About | Resume PDF, contact, skills grouped by the concept matrix | As needed |

Content flow: issue evidence -> weekly devlog -> robot page at each milestone.
