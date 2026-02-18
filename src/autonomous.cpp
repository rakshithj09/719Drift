#include "main.h"
#include "globals.h"
#include "odometry.h"

void autonomous() {
    // Start intake to collect balls
    intake_set(100); // gentle speed to avoid drift
    pros::delay(500); // let intake spin up

    odom::odometry.reset(0.0, 0.0, 0.0);

    // Drive forward slowly to collect 3 balls
    pros::Motor lf(DRIVE_LF_PORT);
    pros::Motor lb(DRIVE_LB_PORT);
    pros::Motor rf(DRIVE_RF_PORT);
    pros::Motor rb(DRIVE_RB_PORT);
    int drive_speed = 60; // slow speed to reduce drift
    lf.move(drive_speed);
    lb.move(drive_speed);
    rf.move(drive_speed);
    rb.move(drive_speed);
    pros::delay(1800); // adjust for distance to 3 balls

    // Stop drive
    lf.move(0);
    lb.move(0);
    rf.move(0);
    rb.move(0);

    // Keep intake running to finish collecting
    pros::delay(500);

    // Score in bottom goal (reverse intake)
    intake_set(-100);
    pros::delay(900); // adjust for scoring time
    intake_set(0);
}
