# 719D Robotics – Pushback 2025-2026

Official VEX V5 codebase for **Team 719D** competing in the **VEX Robotics Competition: Pushback (2025-2026 season)**.  
This repository contains all robot control logic, autonomous routines, and driver programs built using **PROS** in **C++**.

---

## Overview

The 719D robot features a **6-motor tank drivetrain**, dual-roller intake, and an **IMU-assisted autonomous system** for precise movement and orientation.  
This repository is organized and configured for direct competition use, following the standard VRC structure (`initialize`, `autonomous`, `opcontrol`).

---

## Core Systems

### Drivetrain
- 6-motor tank configuration (3 left, 3 right)
- Tuned for accurate straight-line motion and smooth turns
- Supports IMU-based correction and autonomous turning

### Intake System
- 3-motor design: top, middle, and back rollers  
- Optimized for stacking and rapid scoring
- Controlled with L1/L2 and R1/R2 buttons during driver mode

### IMU Control
- Inertial Measurement Unit on Smart Port 10  
- Used for angle tracking and closed-loop turning during autonomous
- Calibrated automatically during initialization

---

## Code Layout

```
src/
│
├── main.cpp                  # competition functions (init, auton, etc.)
├── opcontrol.cpp             # driver control logic
├── turn_imu.cpp              # IMU-based turning helpers
│
├── autonomous.cpp            # placeholder
├── initialize.cpp            # placeholder
├── competition_initialize.cpp # placeholder
├── disabled.cpp              # placeholder
└── on_center_button.cpp      # placeholder
```

Only `main.cpp`, `opcontrol.cpp`, and `turn_imu.cpp` contain control logic.  
The other files exist to maintain a compliant PROS structure.

---

## Autonomous Logic

### Default Sequence
1. Drive forward for 0.8 seconds  
2. Execute a 90-degree IMU-assisted turn  
3. Drive backward for 0.5 seconds  

These parameters are adjustable in `autonomous()` inside `main.cpp`.

---

## Driver Control

| Control | Function |
|----------|-----------|
| Left joystick (Y) | Forward and backward |
| Right joystick (X) | Turning |
| L1 | Intake in |
| L2 | Outtake |
| R1 | Basket to mid |
| R2 | Basket to top |

---

## Technical Notes

- Built using **PROS 4.x** with **C++17**
- Designed for **VEX V5 Brain**
- IMU calibration and motor configuration handled in `initialize()`
- Standard brake modes and gearing set for blue cartridges (600 RPM)

---

## Team Information

**Team:** 719D – Bentonville West High School  
**Season:** VEX V5 Pushback (2025-2026)  
**Language:** C++ with PROS  
**Robot Type:** Competition Standard – Tank Drivetrain, IMU, Intake Mechanism

**Primary Contributors**
- Rakshith Jayakarthikeyan – Lead Programmer
- Eshwar Atmakuri - Assistant Programmer
- Vishwaksen Paramkusham - Float Programmer
- Team Members:
  -   Eshwar Atmakuri
  -   Harshita Chauhan
  -   Prasenjit Panigrahi
  -   Rakshith Jayakarthikeyan
  -   Srivykunth Rubesh
  -   Sujiith Selvakumar
  -   Vishwaksen Paramkusham
  -   Yeshwanth Mathavan

---

## Repository Purpose

This repository serves as a public reference for judges, collaborators, and technical reviewers.  
It demonstrates clean organization, consistent structure, and reliable competition-level code suitable for inspection and replication by other teams.
