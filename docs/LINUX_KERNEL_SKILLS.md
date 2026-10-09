# Linux kernel skills for robotics

An exhaustive list of Linux kernel skills, ordered from prerequisites to maintainership, with
the parts that matter most for robots called out. Kernel work only; for the rest of the stack
see `SKILLS_MAP.md`.

**Where the kernel sits in a robot:** on the robot's main computer (for example the racecar's
single-board computer), between the hardware and your user-space programs. Camera frames, IMU
readings, encoder counts, CAN messages, GPIO and PWM all pass through kernel drivers before
ROS 2 or your AI code sees them. Microcontroller firmware does not run Linux and is not covered here.

**Depth levels** used in the tables:
D1 understand · D2 build it yourself (a module, a test driver) · D3 use and debug it on a real
board · D4 get a patch merged upstream · D5 review others' patches or maintain code.

Robot relevance: ★★★ directly used by your robots · ★★ used indirectly or often · ★ general kernel knowledge.

---

## 1. Prerequisites

| Skill | What to learn | Target depth | Robot relevance |
|---|---|---|---|
| C for the kernel | Pointers, bit manipulation, structs and unions, macros, GNU C extensions, `container_of`, error paths with `goto`, `ERR_PTR`/`IS_ERR`, no libc | D2 | ★★★ |
| Computer architecture | ARM64 and x86 basics, privilege levels, caches, memory ordering, MMIO, interrupts, DMA, IOMMU | D1-D2 | ★★★ |
| Operating system concepts | Processes, threads, virtual memory, system calls, scheduling, synchronisation | D1 | ★★ |
| Git in depth | Rebasing patch series, `git format-patch`, `git bisect`, `git blame`/`log -S` archaeology | D3 | ★★ |
| Build tooling | Make, Kbuild, Kconfig, cross-compilers (`aarch64-linux-gnu-gcc`, clang) | D2 | ★★ |
| Reading datasheets | Register maps, timing diagrams, errata | D3 | ★★★ |
| Test environment | QEMU, a minimal initramfs (BusyBox), `virtme-ng`, serial console on real boards | D3 | ★★ |

---

## 2. Build, boot and development workflow

| Skill | What to learn | Target depth | Robot relevance |
|---|---|---|---|
| Configuring and building | `defconfig`, `menuconfig`, config fragments, building for ARM64 boards | D3 | ★★★ |
| Modules | Out-of-tree and in-tree modules, module parameters, loading/unloading, symbol exports | D2 | ★★ |
| Booting | Boot flow on ARM boards (bootloader -> kernel -> init), kernel command line, device tree blobs | D3 | ★★★ |
| Mainline vs vendor kernels | Why board vendors ship forked kernels; running mainline on a board; finding what is missing upstream | D3 | ★★★ |
| Fast iteration | QEMU boot loops, `virtme-ng`, network boot or SD-card swaps on boards | D3 | ★★ |

---

## 3. Core kernel concepts

| Area | Topics | Target depth | Robot relevance |
|---|---|---|---|
| Kernel/user boundary | System calls, `copy_to_user`/`copy_from_user`, ioctl, uAPI stability rules ("don't break user space") | D2 | ★★ |
| Processes and scheduling | `task_struct`, kthreads, scheduling classes (EEVDF fair scheduler in recent kernels, real-time FIFO/RR, deadline) | D1-D2 | ★★★ (control loops) |
| Interrupts | Top and bottom halves, threaded IRQs, softirqs, BH workqueues (replacing tasklets), IRQ affinity | D2 | ★★★ |
| Deferred work | Workqueues, kthreads, completions, wait queues | D2 | ★★ |
| Time | Jiffies, hrtimers, clocksource/clockevent, timekeeping, `ktime` | D2 | ★★★ (timestamps, control periods) |
| Memory | Pages and zones, `kmalloc`/GFP flags, slab, `vmalloc`, CMA, page cache basics, `mmap` | D1-D2 | ★★ |
| DMA | DMA API, coherent vs streaming mappings, DMA engine, IOMMU | D2 | ★★★ (cameras, high-rate sensors) |
| Concurrency | Atomics, memory barriers, spinlocks, mutexes, rw-semaphores, seqlocks, per-CPU data, RCU | D2 | ★★★ |
| Lifetime | `kref`, `refcount_t`, resource-managed (`devm_*`) allocation | D2 | ★★ |
| Data structures | Linked lists, hlist, rbtree, xarray, `kfifo` (sensor sample buffers) | D2 | ★★ |
| Interfaces to user space | sysfs, debugfs, procfs, character devices, netlink, configfs | D2 | ★★★ |
| Power management | Runtime PM, system suspend, clocks and regulators being turned off | D1-D2 | ★★ (battery robots) |

---

## 4. The driver model

| Skill | What to learn | Target depth | Robot relevance |
|---|---|---|---|
| Bus / device / driver | Matching, `probe`/`remove`, deferred probe | D3 | ★★★ |
| Platform devices | Non-discoverable devices on embedded boards | D3 | ★★★ |
| Device tree | Writing nodes, overlays, bindings in YAML, validating with `make dt_binding_check` and `dtbs_check` | D3-D4 | ★★★ |
| ACPI basics | How x86 boards describe devices | D1 | ★ |
| regmap | Register access abstraction for I2C/SPI/MMIO chips | D3 | ★★★ |
| Clocks, regulators, resets | Common clock framework, regulator framework, reset controllers | D2 | ★★ |
| Pin control and GPIO descriptors | pinctrl, `gpiod_*` API | D3 | ★★★ |
| Interrupt controllers | IRQ domains, interrupts described in device tree | D2 | ★★ |

---

## 5. Subsystems that matter for robots

| Subsystem | What it handles in a robot | Skills to build | Target depth | Robot relevance |
|---|---|---|---|---|
| **IIO** (Industrial I/O) | IMUs, accelerometers, gyros, ADCs, current and voltage sensors | Channels, triggered buffers, triggers, events, scan elements, `libiio` from user space; writing or fixing a sensor driver | D3-D4 | ★★★ |
| **Counter** | Quadrature encoders, timer-capture counters | Counts, signals, synapses, events, the counter character device | D3-D4 | ★★★ |
| **SocketCAN** and CAN drivers | Joint buses, vehicle buses | `net_device` basics, CAN/CAN FD controllers, bit timing, error states and bus-off, `can-utils`, USB-CAN adapters (e.g. `gs_usb`) | D3-D4 | ★★★ |
| **GPIO** | Limit switches, enables, e-stop inputs | gpiolib, the GPIO character device (v2 uAPI), `libgpiod` | D3-D4 | ★★★ |
| **PWM** | Servos, ESC signals, fans | PWM chips and consumers, sysfs interface | D3-D4 | ★★★ |
| **I2C and SPI** | Most sensor buses | Adapter vs client drivers, `spidev`, transfers, error handling | D3-D4 | ★★★ |
| **Serial / TTY, serdev** | Lidars, GPS, MCU links over UART | UART drivers, serdev for devices attached to UARTs | D2-D3 | ★★★ |
| **V4L2 / media, UVC** | Cameras (USB and MIPI CSI) | videobuf2, sub-devices, media controller, formats, UVC quirks | D3-D4 | ★★★ |
| **Input** | Gamepads and joysticks for teleop | Input events, force feedback | D2 | ★★ |
| **USB** | Cameras, adapters, MCU links | Host drivers, gadget mode (board appears as a device) | D2 | ★★ |
| **PTP hardware clocks** | Time-synchronising sensors and computers | `drivers/ptp`, hardware timestamping | D2-D3 | ★★ |
| **hwmon, thermal, power supply** | Temperatures, fan control, battery state | Sensor drivers, thermal zones and cooling devices, battery fuel gauges | D3 | ★★ |
| **Watchdog** | Resetting a hung robot computer | Watchdog drivers and the `/dev/watchdog` interface | D2-D3 | ★★★ (safety) |
| **LED** | Status indicators | LED class, triggers | D2 | ★ |
| **remoteproc / rpmsg** | Linux on a Cortex-A talking to a Cortex-M on the same chip | Loading MCU firmware, messaging channels | D2-D3 | ★★ |
| **DRM / accel** | GPUs and AI accelerators (NPUs) | How jobs and memory are handed to accelerators (`drivers/accel`) | D1-D2 | ★★ (edge AI) |
| **Networking basics** | Robot-to-robot and ROS 2 traffic | Socket buffers, NAPI, offloads, basic tuning | D1-D2 | ★★ |

---

## 6. Real-time Linux for control loops

| Skill | What to learn | Target depth | Robot relevance |
|---|---|---|---|
| PREEMPT_RT (in mainline since 6.12) | Sleeping spinlocks, threaded interrupts, priority inheritance (`rt_mutex`) | D2-D3 | ★★★ |
| Latency sources | IRQs, softirqs, SMIs, frequency scaling, idle states, cache effects | D2 | ★★★ |
| Tuning | IRQ affinity, `isolcpus`, `nohz_full`, `rcu_nocbs`, disabling deep idle states | D3 | ★★★ |
| Measurement | `cyclictest`, `rtla timerlat` / `osnoise`, tracing latency spikes | D3 | ★★★ |
| Scheduling policies | SCHED_FIFO, SCHED_RR, SCHED_DEADLINE, priority planning | D3 | ★★★ |

---

## 7. Debugging, tracing and testing

| Skill | Tools | Target depth | Robot relevance |
|---|---|---|---|
| Logging | `printk`, `pr_debug`, dynamic debug, `dmesg` | D3 | ★★★ |
| Reading crashes | Oops and panic decoding, `decode_stacktrace.sh`, `addr2line` | D3 | ★★★ |
| Tracing | ftrace (function, function_graph), tracepoints, trace events, kprobes, `trace-cmd`, KernelShark | D3 | ★★★ |
| Profiling | `perf` | D3 | ★★ |
| eBPF | `bpftrace`, BCC tools | D2-D3 | ★★ |
| Sanitizers and checkers | KASAN, KCSAN, UBSAN, KMSAN, lockdep, kmemleak, fault injection | D3 | ★★ |
| Unit and self tests | KUnit, kselftest | D3-D4 | ★★ |
| Fuzzing | syzkaller, reading syzbot reports | D2-D3 | ★ |
| Interactive debugging | QEMU + gdb, kgdb, crash dumps (kdump) | D2-D3 | ★★ |
| Finding regressions | `git bisect` across kernel versions | D3 | ★★ |
| CI | KernelCI results for your boards | D2 | ★ |

---

## 8. Code quality and static analysis

| Skill | Tools | Target depth |
|---|---|---|
| Coding style | `Documentation/process/coding-style.rst`, `checkpatch.pl` | D4 |
| Static analysis | sparse, smatch, clang builds, `W=1` warnings | D3 |
| Semantic patches | Coccinelle (automated, tree-wide fixes) | D2-D3 |
| Documentation | kernel-doc comments, `Documentation/` in reStructuredText | D4 |
| Rust in the kernel (optional) | Rust-for-Linux abstractions and drivers | D1-D2 |

---

## 9. Contribution process and community

| Skill | What to learn | Target depth |
|---|---|---|
| Development cycle | Merge window, -rc releases, subsystem trees, linux-next, stable trees | D1 |
| Finding the right people | `MAINTAINERS`, `get_maintainer.pl`, subsystem mailing lists, lore.kernel.org archives | D4 |
| Sending patches | Plain-text email, `git send-email` or `b4`, cover letters, versioned series (v2, v3) with changelogs | D4 |
| Patch tags | `Signed-off-by` (Developer Certificate of Origin), `Fixes:`, `Reported-by`, `Reviewed-by`, `Tested-by`, `Cc: stable` | D4 |
| Responding to review | Addressing every comment, explaining trade-offs, resubmitting cleanly | D4 |
| Rules | No regressions, uAPI stability, stable-kernel rules | D4 |
| Reviewing and testing others' patches | Giving `Reviewed-by` / `Tested-by` on hardware you own | D5 |
| Maintaining | A `MAINTAINERS` entry for a driver you wrote | D5 |
| Security process | Reporting bugs privately; the kernel has issued its own CVEs since 2024 | D1 |
| Community | KernelNewbies, LFX mentorship, Outreachy, Linux Plumbers Conference, Embedded Linux Conference | — |

---

## 10. Embedded Linux around the kernel

| Skill | What to learn | Target depth | Robot relevance |
|---|---|---|---|
| Bootloader | U-Boot, boot scripts, loading kernel + device tree | D3 | ★★★ |
| Build systems | Buildroot, Yocto (kernel recipes, BSP layers) | D3 | ★★★ |
| Upstreaming vendor code | Turning a vendor BSP patch into a mainline-quality series | D4 | ★★★ |
| Verified and secure boot | Signed images, chain of trust | D2 | ★★ |
| Updates | A/B partitions, RAUC, SWUpdate, Mender | D2-D3 | ★★ |
| Hardening basics | Kernel config hardening, lockdown, seccomp, LSMs (SELinux, AppArmor, Landlock) | D1-D2 | ★ |

---

## 11. A robotics-focused contribution path

Ordered so each step builds on the last and uses hardware from your robots.

| Step | Contribution | Skills used | Evidence |
|---|---|---|---|
| 1 | Build and boot mainline on the robot computer (e.g. the racecar's board); note what doesn't work | Sections 2, 4 | Boot log, list of gaps |
| 2 | First patch: a documentation fix, warning fix or small bug in a subsystem you use | Sections 8, 9 | Merged patch |
| 3 | Read sensors from user space through the kernel: IMU via IIO, encoders via counter, CAN via SocketCAN, I/O via `libgpiod` | Section 5 | Working ROS 2 node using kernel interfaces |
| 4 | Measure real-time latency on the robot computer; tune it; publish the numbers | Section 6 | Latency histograms before and after |
| 5 | Fix or extend a driver for a part you actually use (check upstream first; it may already exist) | Sections 3-5, 7 | Merged patch series |
| 6 | Device tree support for your board or sensor, with bindings that pass validation | Section 4 | Merged DT and bindings |
| 7 | Review and test others' patches in that subsystem on your hardware | Section 9 | `Tested-by` / `Reviewed-by` tags |
| 8 | Write a new driver for a part with no upstream support, and maintain it | All | Merged driver, `MAINTAINERS` entry |

Realistic timing: a first merged patch within months; a driver merged and maintained over
a year or more.

---

## 12. Roles these skills lead to

| Role | Most relevant sections |
|---|---|
| Embedded Linux engineer | 2, 4, 5, 10 |
| BSP / board bring-up engineer | 2, 4, 10 |
| Kernel / device driver engineer | 3, 4, 5, 7, 9 |
| Real-time / controls platform engineer | 3, 6, 7 |
| Robotics platform engineer (robot computer, sensors, timing) | 5, 6, 10 |
