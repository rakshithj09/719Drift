# 719D PROS Robotics Code

This repository contains the official **VEX V5 PROS** code for Team **719D**.  
It is designed for the **Pushback** competition game and includes full drivetrain, intake, and IMU-based autonomous control.

---

## Project Overview

**Environment:** PROS 4.x  
**Language:** C++  
**Platform:** VEX V5 Brain and Controller

### Key Features
- 6-motor tank drivetrain with correct gearing and reversal  
- Integrated IMU-based turning (`turn_imu.cpp`)  
- Calibrated IMU at startup for reliable autonomous turns  
- Driver control with arcade steering and intake mapping  
- Safe motor configuration (no deprecated constructors)  
- Ready for official VRC competition template (`initialize`, `autonomous`, `opcontrol`, etc.)

---

## File Structure

```
src/
│
├── main.cpp                  # competition functions: init, auton, etc.
├── opcontrol.cpp             # driver control logic
├── turn_imu.cpp              # IMU-based turning helpers (no include in main)
│
├── autonomous.cpp            # empty placeholder
├── initialize.cpp            # empty placeholder
├── competition_initialize.cpp # empty placeholder
├── disabled.cpp              # empty placeholder
└── on_center_button.cpp      # empty placeholder
```

> Only `main.cpp`, `opcontrol.cpp`, and `turn_imu.cpp` contain logic.  
> The other files exist so PROS compiles cleanly with no duplicate definitions.

---

## Port Map

| Device | Description | Port | Notes |
|---------|--------------|------|-------|
| **Drive Left Front** | Motor | 1 | Blue cartridge |
| **Drive Left Mid** | Motor | 2 | Blue cartridge |
| **Drive Left Back** | Motor | 3 | Blue cartridge |
| **Drive Right Front** | Motor | 4 | Blue cartridge, reversed |
| **Drive Right Mid** | Motor | 5 | Blue cartridge, reversed |
| **Drive Right Back** | Motor | 6 | Blue cartridge, reversed |
| **Front Bottom Intake** | Motor | 7 | Regular |
| **Back Intake** | Motor | 8 | Reversed |
| **Front Top Intake** | Motor | 9 | Regular |
| **IMU** | Sensor | 10 | Used for autonomous turning |

> Update these port numbers in `main.cpp` if your wiring differs.

---

## Autonomous Routine

**Default sequence:**
1. Drive forward for ~0.8 seconds  
2. Turn right 90° using the IMU  
3. Drive backward for ~0.5 seconds  

You can modify the time or direction in `autonomous()` inside `main.cpp`.

---

## Driver Control Mapping

| Control | Function |
|----------|-----------|
| Left joystick Y | Drive forward/back |
| Right joystick X | Turning |
| L1 | Intake in |
| L2 | Outtake |
| R1 | Basket to middle |
| R2 | Basket to top |

Drive includes a small **slew rate** limit for smoother acceleration.

---

## Build and Upload

Run these commands in VS Code terminal:

```bash
pros make clean
pros build
pros upload --slot 1
```

If PROS cannot find your brain:
- Ensure the V5 brain is powered on.  
- Close other VEX utilities.  
- Try another USB port.  
- Re-run with:  
  ```bash
  pros upload --port /dev/cu.usbmodemXXXX
  ```

---

## Troubleshooting

| Issue | Likely Cause | Fix |
|--------|---------------|-----|
| Motors not moving | Wrong ports or wiring | Check brain port map |
| Robot drives backward | Flip `set_reversed` values in `configure_motors()` |
| IMU turn inaccurate | Wait for IMU calibration to finish in `initialize()` |
| “Constructor doesn’t match” error | Use simple `pros::Motor(port)` constructors |
| Duplicate definitions | Delete or empty extra `.cpp` files in `src/` |

---

## Contributors

- **Rakshith Jayakarthikeyan** — Lead programmer  
- **Vishnu**, **Havish**, **Aarman**, **Shashank**, **Abdullah**, **Jackson** — Robotics build and testing team

---

## License

This codebase is for educational and competition use within **Bentonville West High School Robotics Team 719D**.  
Free to reuse with credit.
