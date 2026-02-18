#include "main.h"
#include "globals.h"
#include "autonomous.h"

static void drive_forward_time(int ms, int speed = 60) {
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

// Example routines. Keep them simple and safe; tune timings on the field.
static void skills_routine(AllianceColor color, FieldSide side) {
    // Skills: drive forward, collect then score
    intake_set(100);
    drive_forward_time(1600, 80);
    pros::delay(200);
    // score
    intake_set(-127);
    pros::delay(900);
    intake_set(0);
}

static void left_lineup_routine(AllianceColor color, FieldSide side) {
    // Left lineup: short forward, turn, score
    intake_set(100);
    drive_forward_time(1200, 70);
    pros::delay(100);
    intake_set(-127);
    pros::delay(700);
    intake_set(0);
}

static void right_lineup_routine(AllianceColor color, FieldSide side) {
    // Right lineup: alternative timing for right side
    intake_set(100);
    drive_forward_time(1400, 70);
    pros::delay(150);
    intake_set(-127);
    pros::delay(700);
    intake_set(0);
}

void autonomous() {
    // Choose and run the selected routine
    AllianceColor color = get_auton_color();
    FieldSide side = get_auton_side();
    AutonRoutine r = get_auton_routine();

    // Safety: brief delay to ensure systems ready
    pros::delay(50);

    switch (r) {
        case AutonRoutine::SKILLS:
            skills_routine(color, side);
            break;
        case AutonRoutine::LEFT_LINEUP:
            left_lineup_routine(color, side);
            break;
        case AutonRoutine::RIGHT_LINEUP:
            right_lineup_routine(color, side);
            break;
        default:
            // fallback
            skills_routine(color, side);
    }
}