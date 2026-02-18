#include "main.h"
#include "pros/motors.hpp"
#include "globals.h"
#include "odometry.h"
#include <cmath>

pros::Controller master(pros::E_CONTROLLER_MASTER);

void drivetrain_control() {
    pros::Motor lf(DRIVE_LF_PORT);
    pros::Motor lb(DRIVE_LB_PORT);
    pros::Motor rf(DRIVE_RF_PORT);
    pros::Motor rb(DRIVE_RB_PORT);

    const int DEADBAND = 10;
    int turn = master.get_analog(ANALOG_LEFT_Y);
    int forward = -master.get_analog(ANALOG_RIGHT_X);

    // Deadband
    if (std::abs(forward) < DEADBAND) forward = 0;
    if (std::abs(turn) < DEADBAND) turn = 0;

    int left = forward - turn;
    int right = forward + turn;

    // Clamp to -127 to 127
    left = std::max(-127, std::min(127, left));
    right = std::max(-127, std::min(127, right));

    lf.move(left);
    lb.move(left);
    rf.move(right);
    rb.move(right);
}

pros::Motor intake_bottom(INTAKE_BOTTOM_PORT);
pros::Motor intake_top(-INTAKE_TOP_PORT); // negative for reversed

void intake_set(int speed) {
    intake_bottom.move(speed);
    intake_top.move(speed);
}

void intake_control() {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        intake_set(127); // Intake in
    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        intake_set(-127); // Intake out
    } else {
        intake_set(0); // Stop
    }
}
