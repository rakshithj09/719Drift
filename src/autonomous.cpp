#include "main.h"
#include "globals.h"

// Skills autonomous for VEX Pushback (time-based template tuned for 719D robot)
// NOTE: This routine is intentionally conservative and time-based. For competition
// use replace time-based moves with encoder/IMU-assisted moves for repeatability.

static void drive_time(int ms, int speed) {
    pros::Motor lf(DRIVE_LF_PORT);
    pros::Motor lb(DRIVE_LB_PORT);
    pros::Motor rf(DRIVE_RF_PORT);
    pros::Motor rb(DRIVE_RB_PORT);
    lf.move(speed);
    lb.move(speed);
    rf.move(speed);
    rb.move(speed);
    pros::delay(ms);
    lf.move(0);
    lb.move(0);
    rf.move(0);
    rb.move(0);
}

static void turn_time(int ms, int left_speed, int right_speed) {
    pros::Motor lf(DRIVE_LF_PORT);
    pros::Motor lb(DRIVE_LB_PORT);
    pros::Motor rf(DRIVE_RF_PORT);
    pros::Motor rb(DRIVE_RB_PORT);
    lf.move(left_speed);
    lb.move(left_speed);
    rf.move(right_speed);
    rb.move(right_speed);
    pros::delay(ms);
    lf.move(0);
    lb.move(0);
    rf.move(0);
    rb.move(0);
}

// Helper: short wait while keeping intake running if needed
static void wait_ms(int ms) {
    const int step = 20;
    for (int t = 0; t < ms; t += step) {
        pros::delay(step);
    }
}

void autonomous() {
    // --- Setup ---
    pros::lcd::initialize();
    pros::lcd::set_text(0, "Auton: SKILLS");

    // 1) Prime intake and collect preloads
    intake_set(127);
    drive_time(1000, 80); // drive forward to pick up field objects
    wait_ms(150);

    // 2) Short retreat and align to scoring zone
    intake_set(0);
    drive_time(400, -80); // back away
    wait_ms(100);

    // 3) Turn towards scoring area (approximate)
    turn_time(500, 80, -80); // in-place right turn (tune ms)
    wait_ms(100);

    // 4) Drive into scoring position while intaking
    intake_set(127);
    drive_time(1200, 90);
    wait_ms(100);

    // 5) Score (outtake)
    intake_set(-127);
    pros::delay(900);
    intake_set(0);

    // 6) Optional: collect more and score again
    // Drive back, intake, return
    drive_time(600, -90);
    intake_set(127);
    drive_time(900, 90);
    intake_set(-127);
    pros::delay(800);
    intake_set(0);

    // Final stop and status
    drive_time(200, 0);
    pros::lcd::set_text(1, "Skills complete (time-based)");
}