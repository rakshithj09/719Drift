# 719D Robotics – Pushback 2025-2026

Official VEX V5 codebase for Team 719D competing in the VEX Robotics Competition: Pushback (2025-2026 season).

This repository contains the competition template and core control structure built using PROS in C++.

---

## Overview

This project is a clean PROS competition template configured for the 719D competition robot.

The code follows the official VRC structure:

- initialize()
- disabled()
- competition_initialize()
- autonomous()
- opcontrol()

The robot is currently configured as a drivetrain-based competition robot and ready for subsystem expansion.

---

## Current Robot Configuration

### Drivetrain
- Tank drive configuration
- Blue gear cartridges (600 RPM)
- Controlled through driver joystick inputs in opcontrol()
- Designed for competition tuning and future expansion

### Brain Display
- LCD initialized in initialize()
- Displays confirmation message on startup

Example:
Init OK shown on brain screen during startup

---

## Code Structure

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

The project follows the standard PROS layout for VEX V5.

---

## Autonomous

Autonomous currently serves as a structured placeholder.

This allows rapid development of:
- Timed routines
- Sensor-based navigation
- IMU turning
- Competition-specific scoring routines

Autonomous logic will be expanded as testing progresses.

---

## Driver Control

Driver control runs continuously in opcontrol().

Current behavior:
- Tank drive joystick control
- Designed for modular subsystem additions

Future additions may include:
- Intake control
- Scoring mechanisms
- Drift correction
- Sensor-assisted drive stabilization

---

## Technical Details

- PROS Kernel: 4.2.1
- PROS CLI: 3.5.x
- Language: C++17
- Target: VEX V5 Brain
- Built using arm-none-eabi toolchain

---

## Team Information

Team: 719D – Bentonville West High School  
Season: VEX V5 Pushback (2025-2026)  
Platform: VEX V5 + PROS  

Primary Contributors:
- Rakshith Jayakarthikeyan – Lead Programmer
- Eshwar Atmakuri – Assistant Programmer
- Vishwaksen Paramkusham – Programmer

Team Members:
- Eshwar Atmakuri
- Harshita Chauhan
- Prasenjit Panigrahi
- Rakshith Jayakarthikeyan
- Srivykunth Rubesh
- Sujiith Selvakumar
- Vishwaksen Paramkusham
- Yeshwanth Mathavan

---

## Repository Purpose

This repository documents the official competition code for Team 719D.

It demonstrates:
- Clean PROS structure
- Competition compliance
- Expandable subsystem design
- Organized version control workflow

This project will evolve as the robot is refined for competition performance.
