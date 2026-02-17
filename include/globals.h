#pragma once
#include "main.h"

// ===== 4 MOTOR DRIVETRAIN =====
// Ports from your wiring
// LF = 12
// LB = 11
// RF = 1
// RB = 5
//
// Use negative to reverse a motor if needed later.

constexpr int DRIVE_LF_PORT = 12;
constexpr int DRIVE_LB_PORT = 11;

constexpr int DRIVE_RF_PORT = 1;
constexpr int DRIVE_RB_PORT = 5;

extern pros::Controller master;

extern pros::MotorGroup left_drive;
extern pros::MotorGroup right_drive;

extern const int DRIVE_DEADBAND;

// Drift trim for driving straight.
// Positive adds to left and subtracts from right.
// Start at 0. Adjust later.
extern int DRIVE_DRIFT_TRIM;

void drive_set(int forward, int turn);
void drive_stop();
void drivetrain_control();

// ===== 2 INTAKE =====
// Ports from your wiring
// Bottom = 13
// Top = 14 (reverse in code if needed)

constexpr int INTAKE_BOTTOM_PORT = 13;
constexpr int INTAKE_TOP_PORT = 14;

void intake_control();
void intake_set(int speed);
void autonomous();
void opcontrol();