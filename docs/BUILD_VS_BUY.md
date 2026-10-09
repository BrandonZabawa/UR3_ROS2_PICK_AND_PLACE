# Build vs buy: hardware purchasing rules

When to buy individual components and design the electronics yourself (electrical and
embedded hardware skills), versus buying an assembled robot or subsystem so you can start
on software (firmware on existing hardware, CV, ML, DL). Applies to every robot.

The decision is made **per subsystem, not per robot**. Most good learning platforms are
hybrids: bought mechanics, your own electronics, your own software.

## 1. Classify what the subsystem is for

| Learning goal | Default | Example |
|---|---|---|
| **G1. Electrical design** (power, motor drives, sensor boards, PCB) | Build from individual components | DUM-E joint driver; R-AV power board |
| **G2. Firmware on hardware** (drivers, control loops, buses, RTOS) | Buy modules or a kit **with open firmware**, write the firmware yourself | Dev board + driver module; VESC-based ESC |
| **G3. Autonomy software** (CV, ML, planning, control at the ROS level) | Buy assembled, or simulate | R-AV chassis and compute; cameras; lidar |
| **G4. Not a learning goal** (commodity parts) | Always buy assembled | Wheels, chassis frames, power supplies, buck converters, connectors, cables |

## 2. Hard rules

1. **Never buy closed firmware for a G2 subsystem.** If you cannot read and replace the
   firmware, it teaches integration, not embedded. Closed is fine for G3 and G4.
2. **Never block a software goal on a hardware build.** If building a subsystem would delay
   a G3 goal by more than one sprint, buy or simulate for the software goal now and build
   the hardware version in parallel.
3. **Buy proven assembled parts for high-energy items until you reach level L3** (below):
   LiPo batteries and chargers, mains-powered supplies, and motor drives above low voltage.
4. **One unknown at a time.** Do not design a new board and new firmware for an untested
   motor in the same step. Replace one bought part with your own while the rest stays known-good.
5. **Every build replaces a working bought part or a working simulation.** You always have a
   reference to compare against.
6. **Budget gate:** if the built version costs more than the assembled version and teaches
   nothing new at your current level, buy it.

## 3. Skill levels and when to move up

Buy at your current level; move up only when the exit criteria are met with evidence on
the board.

| Level | What you buy | What you build | Exit criteria (all, with evidence) |
|---|---|---|---|
| **L0. Simulation** | Nothing | Software against a simulator | A working closed loop in sim; metrics recorded |
| **L1. Modules** | Dev boards, breakout boards, driver modules, assembled platform | Firmware, wiring between modules | ≥3 peripherals or buses brought up from the datasheet (e.g. PWM, ADC+DMA, UART/CAN); one fault debugged with a logic analyzer or scope; a closed-loop motor running |
| **L2. Components and harness** | Individual parts: connectors, fuses, regulators, sensors, motors | Wiring harness, power distribution on perfboard, sensor integration | A documented schematic and power budget; harness built and working; fault cases tested (reverse polarity, short, brown-out) on a current-limited supply |
| **L3. Custom PCB** | Bare PCBs from a fab, components | Your own boards | A board designed, reviewed against a checklist, fabricated, brought up, with errata documented; then v2 fixing them |
| **L4. Power and safety** | Components for high-power stages | Motor drives, battery management, safety circuits | L3 met twice; a written hazard analysis; protective equipment and procedures in place |

Different robots can be at different levels, and different subsystems on one robot can too.

## 4. Decision checklist per subsystem

Answer in order; the first rule that fires decides.

1. Is it G4 (commodity, no learning value)? **Buy assembled.**
2. Is it a high-energy item and you are below L4? **Buy proven assembled.**
3. Is it G3 (software is the goal)? **Buy assembled or simulate**, unless the hardware is
   already built and working.
4. Is it G2 (firmware is the goal)? **Buy modules or open-firmware hardware** at your level;
   write the firmware.
5. Is it G1 (electrical design is the goal) and you meet the entry level for it? **Build**,
   keeping a bought reference part for comparison.
6. Would building delay a primary robot's milestone by more than one sprint? **Buy now, build
   later** as a secondary item.

Record the decision on the issue: subsystem, goal (G1-G4), your level, rule that fired.

## 5. Applied to current robots

### R-HW (DUM-E)

| Subsystem | Goal | Level now | Decision |
|---|---|---|---|
| Joint motor + gearbox | G4 | — | Buy (gearmotor with encoder); print reductions later |
| Motor driver | G2 now, G1 later | L1 | Buy a driver module now; own driver board at L3 |
| Controller | G2 | L1 | Buy a dev board with debugger; own board at L3 |
| CAN transceiver | G2 | L1 | Buy breakout; on own board at L3 |
| Bench supply, e-stop parts | G4 | — | Buy |
| Links, brackets | G4 | — | Print (makerspace/service) |

### R-AV (racecar)

| Subsystem | Goal | Level now | Decision |
|---|---|---|---|
| Chassis, suspension, steering servo | G4 | — | Buy assembled RC chassis |
| ESC | G2 | L1 | Buy a VESC-based ESC (open firmware); read and modify firmware later |
| Compute (single-board computer) | G3 | — | Buy |
| Lidar / camera | G3 | — | Buy |
| IMU, wheel encoders, I/O MCU | G2 -> G1 | L1 | Breakout boards + dev board first (stage C); own I/O board at L3 |
| Power distribution, kill switch | G1 | L1 -> L2 | Bought fused distribution first; own board at L2/L3 |
| LiPo battery + charger | High-energy | below L4 | Buy proven assembled; fireproof bag; never charge unattended |

### R-SIM, R-VS, R-CLUB

R-SIM is L0 (simulation only). R-VS and R-CLUB: run each subsystem through section 4
when their hardware is known.

## 6. Schedule implications

- Buying assembled for G3 lets software milestones start in the same sprint as the order.
- Building for G1 adds at least one sprint per board revision (design, fabrication and
  shipping, bring-up); plan the software primary on another robot during that time.
- Move up one level per robot per milestone at most. Faster usually means two unknowns at once.
