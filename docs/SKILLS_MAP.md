# Skills map: from the AI stack to the metal

An exhaustive list of topics for robotics work, from AI down to hardware, organised so each
one is learned **deeply** rather than just used. Every topic says where it shows up in your
robots, where you can contribute upstream (Linux kernel, robotics firmware, ROS, AI
libraries), and the keywords it maps to.

Robot IDs refer to `PLANNING.md` (R-SIM UR3 suite, R-HW DUM-E, R-AV racecar). Deliverable IDs
(CV-*, ML-*, EMB-*, HW-*, SW-*) refer to `DELIVERABLES.md` and `HARDWARE_BUILD_ROADMAP.md`.

---

## 0. The depth ladder (applies to every topic)

| Level | Name | What you do | Evidence |
|---|---|---|---|
| D1 | Understand | Read the theory; work examples by hand | Notes, derivations |
| D2 | Build from scratch | Implement a minimal version yourself, no library | Repo + tests |
| D3 | Use in production form | Use the real tool or library on a robot, measure it | Results table, plots |
| D4 | Contribute upstream | Fix, improve or add to the real project | Merged patch / PR |
| D5 | Teach | Explain it publicly with your own data | Blog post or video |

Aim for D3 on most topics, D4-D5 on the ones that define your specialisation. A topic only
counts as "known deeply" at D2 or above.

---

## 1. The full robot pipeline (why every layer matters)

```
 camera / lidar / IMU / encoders
        |  kernel drivers (V4L2, IIO, counter, SocketCAN)      <- Linux kernel
        |  firmware on MCUs (sampling, timing, control loops)  <- embedded
        v
 perception (CV, DL)  ->  state estimation  ->  planning  ->  control
        |                                                    |
   edge AI runtime (ONNX, TensorRT, NPU drivers)             |  ros2_control
        v                                                    v
 ROS 2 / DDS middleware  ------------------------------>  firmware motor loop  ->  power stage  ->  motor
```

Engineers who can trace a problem across this whole path (for example "the detector is
late because the camera driver drops frames under load, which starves the planner") are
rare. That end-to-end view is what the topics below build toward.

---

## 2. AI layer

### 2.1 Mathematical foundations

| Topic | Build-from-scratch exercise | In your robots | Keywords |
|---|---|---|---|
| Linear algebra (SVD, eigen, least squares, conditioning) | Implement least-squares calibration and PCA with NumPy only | R-SIM calibration, pose PCA | linear algebra |
| Probability and statistics (Bayes, distributions, estimation, hypothesis testing) | Bootstrap confidence intervals for your mAP results | ML-6 ablations | statistics, uncertainty |
| Optimisation (gradient descent, Newton, Gauss-Newton, Levenberg-Marquardt, convex basics) | Write LM for hand-eye or ICP refinement | R1 calibration, R3 pose | nonlinear optimisation |
| Lie groups SO(3)/SE(3), quaternions | Implement exp/log maps and interpolation | Every pose in every robot | 3D geometry, rigid-body transforms |
| Numerical methods (integration, stability, floating point) | Integrate a motor model with Euler vs RK4, compare stability | EMB-2, HW-11 | numerical methods |

### 2.2 Classical machine learning

| Topic | Exercise | In your robots | Keywords |
|---|---|---|---|
| Regression, classification, regularisation | Fit friction models from joint logs | HW-11 system ID | ML fundamentals |
| Clustering, PCA, dimensionality reduction | Segment point clouds with DBSCAN | CV-3 | unsupervised learning |
| Gaussian processes, Bayesian methods | GP model of motor torque ripple | R-HW | Bayesian ML |
| Anomaly detection | Detect joint faults from current signatures | R-HW telemetry | predictive maintenance |

### 2.3 Deep learning fundamentals

| Topic | Exercise | In your robots | Keywords |
|---|---|---|---|
| Backprop, autodiff, optimisers, initialisation | Write a tiny autodiff engine, train an MLP | ML-4 | deep learning, PyTorch |
| CNNs, normalisation, regularisation, augmentation | CNN classifier from scratch | ML-4 | CNN |
| Sequence models, attention, transformers | Implement attention; train a small transformer on joint trajectories | ML-11 | transformers |
| Training dynamics (LR schedules, mixed precision, overfitting diagnosis) | Ablate on YOLO training | ML-6 | model training |
| Uncertainty (ensembles, MC dropout, calibration) | Reliability diagrams for your detector | ML-10 | uncertainty estimation |

### 2.4 Computer vision

| Topic | Exercise | In your robots | Upstream target | Keywords |
|---|---|---|---|---|
| Image formation, pinhole and distortion models | Project 3D boxes to labels | R2 dataset | OpenCV | camera models |
| Camera and hand-eye calibration | Your own solver vs OpenCV | R1, HW-17, R-AV extrinsics | OpenCV, ROS camera_calibration | calibration |
| Multi-view geometry (epipolar, homography, PnP, triangulation) | Stereo depth from infra cameras | CV-2, CV-4 | OpenCV | 3D vision |
| Features and matching (ORB, SIFT, RANSAC) | Feature-based pose | CV-4 | OpenCV | feature matching |
| Detection, segmentation, tracking | YOLO fine-tune; Kalman tracker | R2, CV-5, CV-8, R-AV cones | Ultralytics (AGPL-3.0), OpenCV | object detection, MOT |
| 6-DoF pose, point clouds, ICP | PCA + ICP vs ground truth | R3, CV-9 | Open3D, PCL | 6-DoF pose estimation, point clouds |
| Visual odometry, SLAM | Monocular VO on wrist camera | CV-11, R-AV | ORB-SLAM-style projects, Nav2 | SLAM |
| Depth estimation, 3D reconstruction, NeRF / Gaussian splatting | TSDF fusion of the workspace | CV-6, CV-12 | Open3D | 3D reconstruction |
| Foundation vision models (open-vocabulary detection, segmentation) | Compare zero-shot vs your fine-tuned detector | CV-13 | Hugging Face | foundation models |

### 2.5 Robot learning

| Topic | Exercise | In your robots | Upstream target | Keywords |
|---|---|---|---|---|
| Imitation learning (behaviour cloning, DAgger, ACT, Diffusion Policy) | BC from recorded demos | ML-11, R-SIM data collector | LeRobot | imitation learning |
| Reinforcement learning (PPO, SAC, model-based) | SAC on reach; PPO on racing in sim | ML-12, R-AV | Stable-Baselines3, Gymnasium | reinforcement learning |
| Sim-to-real, domain randomisation, system ID | Randomise and measure the gap | ML-7, HW-11 | MuJoCo, Gazebo | sim-to-real |
| World models, learned dynamics | Predict joint states from commands | ML-13 | — | model-based learning |
| Vision-language-action models | Fine-tune and evaluate honestly | ML-14 | LeRobot, OpenVLA | VLA, embodied AI |
| LLM task planning with safety guardrails | Planner that only emits validated actions | R-SIM llm planner | — | LLM agents for robotics |

### 2.6 Data for ML

| Topic | Exercise | Keywords |
|---|---|---|
| Synthetic data generation and labelling | R2 generator | synthetic data |
| Dataset curation, leakage checks, dataset cards | ML-3 | data-centric AI |
| Active learning, hard-example mining | ML-9 | active learning |
| Evaluation design and metrics (mAP, ADD-S, success rate, lap time) | ML-2 own mAP | evaluation, benchmarking |

### 2.7 ML systems and MLOps

| Topic | Exercise | Keywords |
|---|---|---|
| Experiment tracking, configs, seeds, reproducibility | ML-1 | MLOps |
| Data and model versioning | DVC or release assets | model registry |
| Training at scale (multi-GPU, mixed precision, data loaders) | Colab then larger GPUs | distributed training |
| CI for models (regression gates on metrics) | ML-15 | ML CI/CD |
| Monitoring in deployment (drift, latency) | Log detector confidence on R-AV | ML monitoring |

### 2.8 Edge AI deployment (where AI meets embedded)

| Topic | Exercise | In your robots | Upstream target | Keywords |
|---|---|---|---|---|
| Export and runtimes (ONNX, ONNX Runtime, TensorRT) | Export YOLO, compare runtimes | ML-8, R-AV | ONNX Runtime | ONNX, TensorRT |
| Quantisation (PTQ, QAT), pruning, distillation | INT8 detector, accuracy vs latency | ML-8 | PyTorch | model compression |
| ML compilers | Compile one model with an ML compiler and compare | R-AV compute | Apache TVM, MLIR-based projects | ML compilers |
| Profiling (latency, memory, power) on GPUs/NPUs | Per-layer timing on the car's computer | R-AV | — | edge AI, profiling |
| TinyML on microcontrollers | Motor-current anomaly detector on the MCU | R-HW | TensorFlow Lite Micro, CMSIS-NN | TinyML |
| NPU/accelerator drivers | Read how an accelerator driver exposes jobs to userspace | — | Linux `drivers/accel` | AI accelerators |

---

## 3. Robotics autonomy layer

| Topic | Exercise | In your robots | Upstream target | Keywords |
|---|---|---|---|---|
| Kinematics (FK, IK, Jacobians, singularities) | Analytical IK for DUM-E | HW-16, R-SIM | MoveIt, KDL | kinematics |
| Dynamics (Newton-Euler, Lagrange, gravity compensation) | Implement RNEA; compare with Pinocchio | HW-16, HW-19 | Pinocchio | rigid-body dynamics |
| Trajectory generation (trapezoid, S-curve, splines, time-optimal) | MCU S-curve generator | EMB-8 | ruckig-style libraries | motion profiles |
| State estimation (KF, EKF, UKF, particle filter, factor graphs) | Particle filter localisation | R-AV, HW-15 | robot_localization, GTSAM | sensor fusion |
| Localisation and mapping (scan matching, ICP/NDT, loop closure) | Lidar scan matcher | R-AV | Nav2, slam_toolbox | SLAM |
| Planning (A*, RRT/PRM, optimisation-based, MPC) | RRT for DUM-E; raceline optimisation | R-AV, R-SIM | OMPL, MoveIt, Nav2 | motion planning |
| Control (PID, LQR, MPC, impedance/admittance, force) | MPC for the car; impedance on DUM-E | R-AV, HW-19 | ros2_controllers | control systems, MPC |
| Manipulation (grasping, contact, task constructors) | Grasp quality from depth | CV-10, R-SIM | MoveIt Task Constructor | manipulation |
| Mobile robot models (bicycle model, pure pursuit, Stanley) | Pure pursuit in sim then on the car | R-AV | F1TENTH stack | autonomous vehicles |
| Task-level autonomy (behaviour trees, state machines, PDDL) | BT over perception outputs | SW-10 | BehaviorTree.CPP, py_trees | behaviour trees |
| Simulation and physics engines | Same robot in Gazebo and MuJoCo, compare | R-SIM, R-AV | Gazebo, MuJoCo | simulation |

---

## 4. Robotics software and middleware

| Topic | Exercise | In your robots | Upstream target | Keywords |
|---|---|---|---|---|
| ROS 2 core (nodes, executors, callback groups, QoS, DDS, tf2, launch, lifecycle, composition) | Measure QoS effects on image latency | All | rclcpp, rclpy, ROS docs | ROS 2 |
| ros2_control (controllers, hardware interfaces) | DUM-E hardware interface | HW-5, EMB-3 | ros2_control, ros2_controllers | ros2_control |
| micro-ROS (ROS 2 on MCUs, XRCE-DDS) | DUM-E or R-AV I/O board as a micro-ROS node | HW-12, R-AV stage C | micro-ROS | micro-ROS |
| Real-time userspace on Linux (SCHED_FIFO, mlockall, priority inheritance, latency) | Real-time control thread, measured with cyclictest | EMB-5 | ros2_control real-time tooling | real-time systems |
| Modern C++ (RAII, move semantics, templates, concurrency, memory model, lock-free) | Lock-free SPSC queue in C++ with tests | All C++ | — | C++17/20 |
| Python for robotics and ML (packaging, typing, NumPy performance) | Vectorise a slow perception node | R-SIM | — | Python |
| Rust (optional; embedded and systems) | Port the servo core to Rust | HW-25 | Embassy, rust-embedded | Rust |
| Software engineering (testing, CI/CD, review, architecture, ADRs, docs) | SW-1 to SW-9 | All | — | software architecture |
| Containers and reproducible environments | Dev container for the whole suite | SW-11 | — | Docker |
| Networking and time sync (UDP/TCP, zero-copy, PTP/NTP, serialisation) | Timestamp alignment across camera and lidar | R-AV | — | distributed systems |
| Security (SROS2, secure boot, supply chain, fuzzing) | Fuzz your frame parser | EMB-6 | SROS2 | robot security |

---

## 5. Linux kernel and embedded Linux

Nobody knows the whole kernel in depth; maintainers specialise. The plan: understand the core
well enough to reason about it, and go deep in the subsystems your robots use.

### 5.1 Kernel core (understand to D1-D2)

| Topic | Exercise | Keywords |
|---|---|---|
| Building, configuring, booting a kernel; modules | Build and boot your own kernel on a board or VM | Linux kernel |
| Process scheduling (EEVDF in recent kernels, real-time classes) | Trace scheduling of your control thread | scheduler |
| Interrupts (top/bottom halves, threaded IRQs, softirqs, workqueues) | Write a module with a threaded IRQ handler | interrupt handling |
| Timers (hrtimers), time keeping | Measure timer jitter | timing |
| Memory management (paging, slab, DMA mapping) | Allocate DMA buffers in a test driver | memory management |
| Concurrency and locking (spinlocks, mutexes, RCU, atomics, lockdep) | Trigger and read a lockdep warning in a test module | kernel concurrency |
| Device model, device tree, sysfs | Describe a sensor in device tree for a dev board | device tree |

### 5.2 Subsystems that matter for robots (go to D3-D4)

| Subsystem | What it is for | In your robots | Contribution ideas |
|---|---|---|---|
| **IIO** (Industrial I/O) | IMUs, ADCs, current/voltage sensors | R-AV IMU, R-HW current sensing | Driver for a sensor you use; fixes to existing drivers |
| **Counter** | Quadrature encoders, timers as counters | R-HW, R-AV wheel encoders | Use it for encoders on a Linux board; improve a driver |
| **SocketCAN / CAN drivers** | CAN buses | R-HW joint bus, R-AV | Driver fixes, documentation, test tools |
| **GPIO, pinctrl, PWM** | Digital I/O, PWM outputs | R-AV servo/ESC, R-HW | Small driver and binding fixes |
| **I2C / SPI** | Sensor buses | All | Bus driver fixes for your board |
| **V4L2 / media, UVC** | Cameras | R-AV, R-HW camera | Driver quirks for a camera you own |
| **remoteproc / rpmsg** | Linux talking to an MCU core on the same chip | Boards with a Cortex-A + Cortex-M | Firmware loading and messaging examples |
| **hwmon, thermal, power supply** | Temperatures, battery monitoring | R-AV power board | Driver for your battery monitor chip |
| **PREEMPT_RT** (real-time, in mainline since 6.12) | Bounded latency for control on Linux | EMB-5, R-AV compute | Report and fix latency issues found by your tests |
| **accel** (`drivers/accel`) | AI accelerators / NPUs | R-AV edge AI | Read first; contribute only once deep in a specific driver |

### 5.3 Debugging, tracing and testing (D3)

`printk` and dynamic debug · ftrace and trace-cmd · `rtla` (osnoise/timerlat) for real-time
latency · perf · eBPF / bpftrace · KASAN and other sanitizers · lockdep · KUnit and
kselftest · syzkaller / syzbot reports · kgdb.

### 5.4 The contribution process (D4)

| Step | What to learn |
|---|---|
| Workflow | git, patch series, `git send-email` or `b4`, `checkpatch.pl`, `get_maintainer.pl` |
| Etiquette | Mailing-list review, responding to feedback, versioned resubmissions (v2, v3) |
| Legal | `Signed-off-by` and the Developer Certificate of Origin |
| Where to start | Documentation fixes, warnings, small bugs, syzbot reports; KernelNewbies; LFX mentorship |
| Growing | A driver for a part on your robots; reviewing others' patches in that subsystem |
| Long term | Becoming a reviewer or maintainer for a driver you wrote |

### 5.5 Embedded Linux (D3)

Bootloaders (U-Boot) · cross-compilation · Buildroot and Yocto · root filesystems · board
support packages · OTA updates (RAUC, SWUpdate, Mender) · read-only root and recovery.

---

## 6. Microcontroller firmware

| Topic | Exercise | In your robots | Upstream target | Keywords |
|---|---|---|---|---|
| MCU architecture (Cortex-M: NVIC, SysTick, MPU, FPU; RISC-V basics) | Startup code and linker script by hand | HW-2 | — | ARM Cortex-M |
| Clock trees, memory maps, startup, linker scripts | Bare-metal blink with no vendor HAL | HW-2 | — | bare metal |
| Peripherals (GPIO, timers, PWM, input capture, quadrature, ADC+DMA, UART, SPI, I2C, CAN/CAN FD, USB) | Each one from the datasheet | HW-3, HW-4 | Zephyr drivers | peripheral drivers |
| RTOS (FreeRTOS, Zephyr, NuttX): scheduling, IPC, priority inheritance | Same control loop on bare metal and on an RTOS | HW-13 | Zephyr (uses devicetree and Kconfig like Linux) | RTOS |
| Motor control (PID, cascaded loops, FOC, SVPWM, observers, encoder calibration) | FOC from scratch on a gimbal motor | HW-9 | SimpleFOC, VESC firmware (GPL-3.0) | motor control, FOC |
| Fixed-point arithmetic, numerical robustness | Q-format PID vs float | EMB-7 | CMSIS-DSP | DSP |
| Communication (custom framing, CANopen, EtherCAT, RS-485/Modbus, micro-ROS) | Your frame protocol; later CANopen basics | HW-4, HW-12 | CANopen stacks, micro-ROS | industrial protocols, EtherCAT |
| Bootloaders, flash, OTA, secure boot | Dual-slot update with rollback | HW-14 | MCUboot | bootloaders |
| Watchdogs, fault handling, safe states | Fault-injection matrix | HW-6, EMB-6 | — | functional safety |
| Testing (host unit tests, HIL, fuzzing, static analysis, MISRA awareness) | Host tests + sanitizers + HIL rig | EMB-1, HW-12 | — | embedded testing |
| Debugging (SWD/JTAG, GDB, OpenOCD/probe-rs, SWO/ITM/RTT, logic analyser, scope) | Trace a timing bug to the cycle | HW-2 onward | OpenOCD, probe-rs | embedded debugging |
| Flight/robot firmware ecosystems | Read their architecture; fix a small issue | — | PX4 (NuttX), ArduPilot, Zephyr | autopilot firmware |

---

## 7. Hardware and electrical

| Topic | Exercise | In your robots | Keywords |
|---|---|---|---|
| Circuit fundamentals, datasheet reading | Bench measurements of every part you add | HW-1 onward | electronics |
| Power electronics (buck/boost, MOSFETs, H-bridges, gate drivers) | Characterise your H-bridge losses | HW-3, HW-9 | power electronics |
| Analog front ends for sensors (filtering, amplification, ADC sampling) | Current-sense front end | HW-9, HW-15 | analog design |
| PCB design (KiCad), signal integrity, grounding, EMC | Board v1 and v2 with errata | HW-8 | PCB design |
| Thermal design and derating | Thermal camera or thermocouple tests | HW-22 | thermal management |
| Batteries and BMS (LiPo safety, monitoring) | Battery monitor on R-AV | R-AV stage D | battery systems |
| Mechanical design and CAD, tolerances, transmissions | Printed reduction for DUM-E | HW-10 | mechanical design |
| Functional safety concepts (ISO 13849, IEC 61508, ISO 10218 awareness) | Written hazard analysis | HW-21 | functional safety |

---

## 8. Cross-cutting systems skills

| Topic | Exercise | Keywords |
|---|---|---|
| End-to-end latency budgets (sensor -> inference -> planning -> control -> actuation) | Measure every stage on R-AV and publish the budget | systems engineering |
| Cross-layer profiling | One problem traced from Python node to kernel driver to firmware | performance engineering |
| Failure mode analysis (FMEA) | FMEA for DUM-E | reliability |
| Architecture and decision records | ADR for every major choice | robotics architecture |
| Technical writing and teaching | Milestone blog posts and videos | communication |
| Open-source practice (reviewing, maintaining, governance, licensing) | Maintain your own repos well; review upstream patches | open source |

---

## 9. Contribution targets by layer

| Layer | Projects to contribute to | Good first contributions |
|---|---|---|
| Linux kernel | IIO, counter, SocketCAN, GPIO/PWM, V4L2, PREEMPT_RT, accel | Docs, warnings, syzbot fixes, a driver for your sensor |
| MCU firmware | Zephyr, SimpleFOC, VESC firmware, micro-ROS, MCUboot, PX4, ArduPilot | Board support for a board you own, examples, bug fixes |
| ROS | ros2_control, ros2_controllers, MoveIt, Nav2, rclcpp, BehaviorTree.CPP | Docs, tests, small features you needed |
| Robotics libraries | Pinocchio, OMPL, Open3D, PCL, GTSAM | Examples, bindings, bug fixes |
| AI | PyTorch, ONNX Runtime, OpenCV, LeRobot, Hugging Face libraries | Docs, examples, export/quantisation fixes |
| Simulation | Gazebo, MuJoCo, F1TENTH gym | Models, examples, bug fixes |

Rule of thumb: contribute where your own robots hit a real limitation. Those patches come
with a real use case, which makes them easier to get accepted and easier to explain.

---

## 10. Role map (where the topics point)

| Role | Core sections |
|---|---|
| Perception / computer vision engineer | 2.1, 2.4, 2.6, 2.8 |
| Machine learning engineer (robot learning) | 2.3, 2.5, 2.6, 2.7 |
| Edge AI / ML deployment engineer | 2.8, 4 (C++), 5.2 (accel, V4L2), 8 |
| Robotics software engineer | 3, 4 |
| Autonomy engineer (mobile robots, AVs) | 2.4, 3, 4 |
| Controls engineer | 2.1, 3 (control, dynamics), 6 (motor control) |
| Embedded firmware engineer | 6, 7 |
| Embedded Linux / BSP / kernel driver engineer | 5, 6 |
| Robotics systems / integration engineer | 4, 5.5, 8 |
| Robotics architect (long-term goal) | All sections at D2+, several at D4, plus 8 |

---

## 11. Choosing what to go deep on

Not everything goes to D4. A sustainable shape:
- **Broad at D2-D3** across sections 2-7, through the robots' normal milestones.
- **Deep at D4-D5** in one AI area (for example 2.4 + 2.8), one low-level area (for example
  5.2 IIO/counter/CAN + 6 motor control), and the bridge between them (2.8 edge AI or
  8 end-to-end latency).
- Add topics to the ideas file and promote them through the normal weekly triage
  (`PLANNING.md`), so depth grows without breaking the schedule.
