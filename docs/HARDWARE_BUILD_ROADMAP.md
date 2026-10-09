# Hardware build roadmap: from a bench motor to a custom arm

Purpose: build robot hardware and its embedded stack yourself, end to end, so that no
closed-source driver or vendor controller stands between you and the concepts. This
is a learning-and-portfolio plan, not a product plan.

It complements `HARDWARE_DELIVERABLES.md` (the simulation-first embedded plan, EMB-*).
Rule of thumb: simulate an idea first when that is cheap, then build it, then compare
measurements with the simulation. IDs here are `HW-*`.

## Assumptions (change them if they are wrong)

- Time: about 6-10 hours a week, shared with other projects.
- Budget: modest, a student/hobby budget. Costs below are rough guesses, not quotes;
  check current prices before ordering.
- You write the firmware yourself. This document lists what to build and how to know
  it works; it contains no firmware.
- Tools you will buy over time: a current-limited bench power supply, a multimeter, a
  logic analyzer, an oscilloscope (a cheap one is fine to start), a debug probe.
- Comfort with soldering is assumed or will be learned in HW-1.

Time estimates are rough and will vary a lot with experience and shipping delays.

## Principles

1. **Bottom up.** One motor, then one joint, then three joints, then an arm.
2. **Every stage has a bench test and a written "done" condition.** No test, not done.
3. **Measure, then model.** Record real data and use it to fix the simulation.
4. **Safety before capability.** Current limit, e-stop and watchdog come before speed.
5. **Study open designs before building your own** (see the reference list), and
   check each project's licence before reusing anything.
6. **Decision gates.** Do not start a tier until the previous tier's definition of
   done is met. Scope creep is the main way hardware projects die.

## Recommended platform choices

These are defaults to reduce decisions, not the only valid ones.

| Decision | Recommendation | Why |
|---|---|---|
| Learning MCU | An STM32 Nucleo board (e.g. a G4 or F4 family part) | Built-in debug probe, good motor-control peripherals, widely used in industry. Verify the exact part's peripherals before buying. |
| Easier alternative | RP2040 (Raspberry Pi Pico) | Cheap, friendly toolchain, fewer motor-control features |
| Joint bus | CAN (classic first, CAN FD later) | Industry standard for actuators; works with Linux SocketCAN |
| Host adapter | A USB-CAN adapter supported by SocketCAN | Lets ROS 2 on Linux talk to your nodes |
| First motor | Brushed DC motor with a quadrature encoder | Simple power stage; teaches PWM, encoders, PID |
| Second motor | BLDC (gimbal or small outrunner) with a magnetic encoder | Teaches FOC, the core of modern actuators |
| Firmware language | C (portable core) with optional Rust port later | C is the industry baseline; Rust is a good stretch |
| PCB tool | KiCad | Free, industry-credible |
| Build/test | CMake + host unit tests + CI cross-compile | Same discipline as the software repo |

## Open designs worth studying first

Read their schematics and firmware structure before designing your own. Verify each
project's current status and licence yourself.

- ODrive, moteus (mjbots), SimpleFOC: open motor controllers/FOC
- MIT Mini Cheetah actuator design and the Open Dynamic Robot Initiative: torque-controlled actuators
- PAROL6, Annin AR4, BCN3D Moveo: open-source desktop arms
- ros2_control documentation and example hardware interfaces: the host-side contract

---

# Tier 1: Hardware MVP (one joint, ROS-controlled)

Target: roughly 3-5 months part-time. Estimated spend: low, in the low hundreds of dollars.

| ID | Item | What you build | You know it works when | Concepts learned |
|---|---|---|---|---|
| HW-1 | Bench and safety setup | Current-limited supply, e-stop that cuts motor power in hardware, labelled bench, written checklist | E-stop cuts power with the firmware dead; checklist reviewed | Power safety, ESD, tooling |
| HW-2 | Dev-board bring-up | Toolchain, debugger, blink, UART logging, timer interrupt, cross-compile in CI | Breakpoints and variable inspection work; CI builds the firmware | Clock tree, GPIO, interrupts, linker/startup basics |
| HW-3 | Closed-loop DC motor | H-bridge, PWM, quadrature encoder on a hardware timer, current sense on an ADC with DMA, a 1 kHz position loop | Measured step response plotted and compared with your simulated motor model | Timers, ADC/DMA, PID in practice, quantisation, noise |
| HW-4 | CAN node | Your own frame protocol on CAN, host-side USB-CAN, error counters, loss/reorder handling | Sustained command/telemetry traffic with injected faults handled | Buses, framing, arbitration, error handling |
| HW-5 | ros2_control hardware interface | A C++ `SystemInterface` plugin that talks to the real joint | `joint_trajectory_controller` moves the real joint; pulling the cable trips the fault state | The software/hardware boundary in ROS 2 |
| HW-6 | Safety and telemetry | Watchdog, current/position/temperature limits, fault log, data logger | Every injected fault produces the expected safe state and log entry | Fault handling, observability |
| HW-7 | MVP write-up | Schematics, photos, step-response and fault-test data, short video, README | A stranger can reproduce the single-joint setup | Documentation as engineering output |

**MVP definition of done:** one joint, driven from ROS 2 over CAN with firmware you
wrote, with a measured step response, a tested e-stop and watchdog, and a write-up.

# Tier 2: Hardware Advanced (custom actuator, multi-joint arm)

Target: roughly 6-9 more months. Estimated spend: a few hundred to about a thousand dollars,
mostly PCBs, motors, printed parts and tools.

| ID | Item | What you build | You know it works when | Concepts learned |
|---|---|---|---|---|
| HW-8 | Custom PCB v1 | KiCad schematic and layout of an MCU + driver + CAN board; fabricate and assemble | Board powers up, programs, and runs HW-3 firmware; a design-review checklist is filled in | Schematic capture, layout, power integrity, bring-up |
| HW-9 | BLDC and FOC | Clarke/Park transforms, SVPWM, current loops, encoder alignment, torque mode | Torque tracks command; speed and position loops sit on top; efficiency measured | Motor control theory, ADC sync with PWM, calibration |
| HW-10 | Actuator mechanics | A geared joint (printed planetary, cycloidal or belt reduction) with encoder mounting | Backlash, friction, efficiency and thermal limits measured and recorded | Transmission design, tolerances, thermal behaviour |
| HW-11 | System identification | Fit motor/joint model parameters from logs; feed them back into the simulator | Simulated and real step responses agree within a stated error | Parameter estimation, sim-to-real |
| HW-12 | Multi-joint bus | 3 joints on one CAN bus with addressing, sync and a bus-load budget | Coordinated motion with measured timing; bus load under a chosen limit | Scheduling, latency, determinism |
| HW-13 | Real-time structure | RTOS (FreeRTOS or Zephyr) or a bare-metal scheduler; jitter measured with a logic analyzer | Worst-case loop jitter and execution time within budget | RTOS, priorities, WCET |
| HW-14 | Firmware update | Bootloader with CRC check, update over CAN, rollback on failure | An interrupted update recovers to a working image | Boot flow, memory maps, field reliability |
| HW-15 | Sensing and estimation | Current/temperature sensing, motor-current force estimate, IMU + encoder fusion | Estimates compared with a reference sensor | Filters, estimation, sensor limits |
| HW-16 | Arm kinematics on hardware | Zeroing, joint limits, gravity compensation, repeatability test | Repeatability measured and reported (mm) | Calibration, kinematics, error budgets |
| HW-17 | Vision on the real arm | Mount a camera; run hand-eye calibration from the software deliverables on real hardware | Real calibration error reported against a measured reference | Where vision and hardware meet |

**Advanced definition of done:** a 3-joint arm on your own boards, controlled through
ROS 2, with a system-identified model, a measured repeatability figure, and a working
firmware-update path.

# Tier 3: Hardware Stretch (full custom arm and productisation)

Target: 12+ months, optional. Costs depend heavily on scope.

| ID | Item | What you build | Concepts learned |
|---|---|---|---|
| HW-18 | 6-DoF custom arm | Full arm from your own actuators and boards, MoveIt integration, light pick-and-place | System integration, tolerance stack-up |
| HW-19 | Torque and impedance control | Backdrivable actuators, joint torque control, compliant behaviour | Force control, stability |
| HW-20 | Custom gripper | Sensor-equipped gripper with current/force feedback | Mechatronics, grasp sensing |
| HW-21 | Functional safety study | Dual-channel e-stop, safe torque off, written hazard analysis. Study ISO 10218 and ISO 13849 concepts; do not claim compliance | Safety engineering |
| HW-22 | EMC and thermal testing | Pre-compliance checks, thermal imaging, derating curves | Real-world reliability |
| HW-23 | Design for manufacture | Cost-reduced BOM, test fixtures, a small build batch | Production thinking |
| HW-24 | Teleoperation | Leader-follower arm with force feedback | Latency, bilateral control |
| HW-25 | Rust port of the core | Port the portable core to Rust (e.g. Embassy) and compare | Memory safety, modern embedded tooling |
| HW-26 | Open-source release | Documented hardware and firmware: BOM, assembly guide, licences, CI | Community-grade engineering |
| HW-27 | FPGA or hardware-accelerated control | Offload a control loop or encoder interface to an FPGA | Hardware/software co-design |

# Embedded concept coverage

| Concept | Where you learn it |
|---|---|
| GPIO, clocks, interrupts, timers, PWM | HW-2, HW-3 |
| ADC, DMA, quadrature decoding | HW-3 |
| UART/SPI/I2C/CAN | HW-2, HW-4, HW-12 |
| Control theory (PID, FOC, cascaded loops) | HW-3, HW-9 |
| Estimation (filters, sensor fusion) | HW-15 |
| RTOS, scheduling, WCET | HW-13 |
| Bootloaders, memory maps, update safety | HW-14 |
| PCB design and bring-up | HW-8, HW-23 |
| Power electronics and thermal design | HW-9, HW-10, HW-22 |
| Testing, CI, debugging, observability | HW-2, HW-6, throughout |
| Safety and fault handling | HW-1, HW-6, HW-21 |
| System identification and sim-to-real | HW-11 |

# Portfolio outputs per stage

Each stage should leave something a stranger can verify:

- A schematic or wiring diagram, and photos of the build.
- A short video of the thing working, and a plot of the measurement behind it.
- A repository folder with source, build instructions, tests, and a README stating
  what was and was not verified on real hardware.
- A one-page "what went wrong and how I fixed it" note. These are what interviewers ask about.

# Practical risks

- **Smoke and burnt parts.** Start with a current-limited supply and low voltage.
  Budget for spares of the cheap parts.
- **Lead times.** PCB fabrication and shipping can take weeks. Do bench work on dev
  boards while boards are in transit.
- **Mechanical scope creep.** The electronics and firmware are the point; keep the
  mechanics as simple as they can be at each tier.
- **Moving targets.** Do not change the protocol and the hardware at the same time.
- **Motors are hazardous.** Even small arms can pinch fingers or throw parts. Keep
  loose clothing and hands clear, and use the e-stop habitually.
- **Simulation is not proof.** Passing tests on a PC does not make hardware safe.

# Suggested sequencing with the software work

| Phase | Software track | Hardware track |
|---|---|---|
| Weeks 0-8 | Class MVP (calibration, YOLO, pose) | HW-1, HW-2 in spare time |
| Months 3-6 | Repo refactor and CI | HW-3 to HW-6 (MVP) |
| Months 6-12 | Perception extensions | HW-8 to HW-12 |
| Year 2 | Learning-based extensions | HW-13 to HW-17, then Stretch by interest |

Keep the class deliverables first. The hardware track is deliberately designed so it
never blocks them.
