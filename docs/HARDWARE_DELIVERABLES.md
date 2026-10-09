# Hardware / embedded deliverables

A separate track from the class work. Purpose: learn embedded and real-time
concepts using this project as the plant, with code that is meant to move to real
hardware later and to be reused in your Viable Solutions arm.

## Status

Nothing in this track is implemented in the repo yet. It is a learning plan: you
write the firmware, and the items below say what to build and how you would know it
works. Suggested approach for EMB-1: plain C11 with no heap, no OS calls, no globals,
and time passed in as a parameter, so the same code runs in host unit tests and on a
microcontroller.

EMB-1 contents to write:

| Module | Purpose |
|---|---|
| PID | Derivative on measurement, filtered derivative, anti-windup, output clamp |
| CRC-16 | CRC-16/CCITT-FALSE; check the standard `"123456789"` -> `0x29B1` vector |
| Framing | Wire format such as `0xA5 | len | type | payload | crc16`; a byte-at-a-time parser that resynchronises after garbage and counts errors |
| Ring buffer | Single-producer/single-consumer byte ring for a UART-ISR to main-loop hand-off |
| Fault FSM | Disabled / Enabled / Fault: command watchdog, overcurrent, position limits, wrap-safe 32-bit ms timing |
| Tests | Host unit tests, then the same tests under AddressSanitizer and UBSan |

Pitfalls worth knowing in advance:

- `float` PID is fine on Cortex-M4F/M7 and ESP32 but slow on an M0 (EMB-7 covers fixed-point).
- A ring buffer is only safe for one producer and one consumer; cores with write
  reordering need the target's memory barrier.
- A frame format without a sequence number or acknowledgement cannot detect lost frames.
- A CRC detects corruption; it does not authenticate.
- Overcurrent and position checks are only as good as the sensor reading you feed them.

## Architecture

```
ROS 2 controllers (joint_trajectory_controller)
        |  position/velocity commands
ros2_control SystemInterface plugin  (C++, EMB-3)   <- the real hardware boundary
        |  frames (frame.c)
transport: vcan / UART / CAN         (EMB-4)
        |
drive firmware: your servo core       <- same code on host and MCU
        |
motor + encoder (simulated first, EMB-2; real later)
```

Everything above the transport line is already how ROS 2 talks to real drives, so
swapping the simulated drive for a physical one changes the bottom layers only.

## Deliverables

Tiers as in `DELIVERABLES.md`. "Verify" says how you would know it works.

### Tier MVP+

**EMB-1: servo core.** See Status above. Verify: host unit tests pass, including garbage-resync, CRC-error, watchdog, and counter-wrap cases.

**EMB-2: simulated joint drive.**
Model a DC motor (J, b, Kt, R, L) plus a quantised encoder in Python or C; close the loop
with your servo core. Tune the PID against the model.
Verify: step response overshoot/settling time within a stated spec; saturation behaviour
without windup; encoder quantisation visible in the derivative term.

**EMB-3: `ros2_control` SystemInterface plugin.**
A C++ hardware plugin that exposes joint position/velocity state and a position command
interface, forwards commands as frames, and reads state frames. Lifecycle: `on_init`,
`on_configure`, `on_activate`, `on_deactivate`. The vendored `src/gz_ros2_control` and
`ur_description/urdf/ros2_control_mock_hardware.xacro` are useful references.
Verify: the existing `arm_controller` drives the simulated drive unchanged; unplugging the
transport triggers the watchdog fault and the controller reports failure rather than hanging.

### Tier Advanced

**EMB-4: virtual CAN.** Use Linux `vcan`/SocketCAN, run the drive simulator as a separate
process, send your frames over it. Verify with injected loss, reordering and delay (`tc netem`).

**EMB-5: real-time-safe loop.** Run the control tick at a fixed rate, measure jitter
(`clock_nanosleep` or a PREEMPT_RT kernel if available), forbid allocation in the loop
(`mlockall`, preallocated buffers). Verify: histogram of period error and worst-case latency.

**EMB-6: fault injection.** Test matrix: dropped frames, corrupted bytes, stuck encoder,
sensor spike, command timeout, overcurrent, power-up in enabled state. Each case has an
expected safe behaviour and an automated test.

**EMB-7: fixed-point PID.** Q-format implementation, compared against the float version over the
same trajectories; report max error and cycle count on a Cortex-M target (or QEMU).

**EMB-8: trajectory generation.** Trapezoidal then S-curve velocity profiles with jerk limits,
evaluated at the control rate; compare against MoveIt's output for the same move.

**EMB-9: RTOS.** Port the loop to FreeRTOS or Zephyr: high-priority control task, comms task,
watchdog task. Demonstrate and then fix a priority inversion.

**EMB-10: safe update.** Dual-slot firmware image with CRC and rollback; test by interrupting
an update.

### Tier Stretch

**EMB-11: FOC.** Clarke/Park transforms, current loops, SVPWM; simulate first, then a bench
BLDC with a proper driver and current sensing.

**EMB-12: hardware-in-the-loop.** Your servo core on a dev board (STM32, RP2040 or ESP32 are
common choices, none tested here); the plant simulated on the PC and linked by UART/CAN.
Verify: step response on hardware matches EMB-2 within a stated tolerance.

**EMB-13: sensor fusion.** IMU + encoder estimation (complementary, then Kalman) on the MCU.

**EMB-14: safety concept.** Written hazard analysis, e-stop chain, safe torque off, limits
enforced in hardware. Software alone is not a safety function.

**EMB-15: real hardware bring-up.** One real joint or gripper, then the arm.

## Porting checklist (host to microcontroller)

1. Keep the core unchanged; provide `now_ms` from a hardware timer and `dt` from the control timer.
2. Push bytes into the ring buffer from the UART/CAN RX interrupt; feed the parser from the main loop.
3. Notify the watchdog on every valid command frame.
4. Check the compiler's `float` and `uint32_t` behaviour on the target; rerun the host tests with the cross-compiler or QEMU.
5. Measure worst-case execution time of one control tick, with margin.

## Real-hardware bring-up rules (read before powering anything)

- Hardware e-stop that cuts motor power independently of software, tested before anything else.
- First power-up: current-limited supply, motor unloaded, low gains, low velocity cap.
- Enforce limits in firmware **and** with physical stops where possible.
- Keep the watchdog enabled from day one; test that it actually trips.
- Do not rely on simulation results as proof of safety.
