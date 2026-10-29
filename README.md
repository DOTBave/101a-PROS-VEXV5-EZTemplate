# 101A VEX V5 Code

[![Build](https://github.com/DOTBave/101a-PROS-VEXV5-EZTemplate/actions/workflows/pros-ci.yml/badge.svg?branch=dev)](https://github.com/DOTBave/101a-PROS-VEXV5-EZTemplate/actions)

Starter code for our V5 robot: PROS 4.1.1 + EZ-Template 3.2.2, four drive motors, tank control.

## Hardware

- V5 Brain with a four-motor drive base (two motors per side)
- V5 Inertial Sensor (IMU) — EZ-Template requires one
- No other mechanisms yet

## Setup

1. Install PROS and the PROS VS Code extension.
2. Open this folder in VS Code.
3. Update the drive ports, IMU port, wheel diameter and wheel RPM at the top of `src/main.cpp`.
4. Build with `make quick` or the PROS sidebar, then download to the brain.

## Controls

- Tank drive: left stick = left side, right stick = right side
- Autonomous selector: use the left/right buttons on the brain screen
- If the robot does not move in autonomous, check the IMU is plugged in and calibrated

## Project Layout

```text
src/main.cpp          drive setup, initialize / autonomous / opcontrol
src/autons.cpp        PID constants and autonomous routines
include/autons.hpp    autonomous function declarations
include/subsystems.hpp  place for intake / lift / other mechanisms
include/EZ-Template/  EZ-Template headers and API
firmware/             PROS kernel and precompiled libraries
```

## Adding an Autonomous Routine

1. Write a function in `src/autons.cpp` using `chassis.pid_drive_set()` and `chassis.pid_turn_set()`.
2. Declare it in `include/autons.hpp`.
3. Add it to the `autons_add({...})` list in `src/main.cpp`.

## Git Workflow

- `master` — working code that has been tested on the robot
- `dev` — daily development, pull requests go here
- `feat/<name>` — short-lived branches for a single change

CI builds every push and pull request to `dev` and `master`
(`.github/workflows/pros-ci.yml`). Open a pull request with the template in
`.github/pull_request_template.md` when a change is ready.

## Notes

- Keep PROS 4.1.1 and EZ-Template 3.2.2. Do not run `pros upgrade`: PROS 4.2.x
  does not work with EZ-Template 3.2.2 (known black screen / crash issue), and
  upgrading EZ-Template to 4.0 is a breaking change.
- Keep comments short and code simple so the next programmer can follow it.

## Credits

- [PROS](https://pros.cs.purdue.edu/)
- [EZ-Template](https://ez-robotics.github.io/EZ-Template/)
