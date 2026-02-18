#include "main.h"
#include "globals.h"
#include "auton_selector.h"

#include <string>

namespace {

void run_three_ball_routine() {
    intake_set(100);
    pros::delay(500);

    pros::Motor lf(DRIVE_LF_PORT);
    pros::Motor lb(DRIVE_LB_PORT);
    pros::Motor rf(DRIVE_RF_PORT);
    pros::Motor rb(DRIVE_RB_PORT);
    int drive_speed = 60;
    lf.move(drive_speed);
    lb.move(drive_speed);
    rf.move(drive_speed);
    rb.move(drive_speed);
    pros::delay(1800);

    lf.move(0);
    lb.move(0);
    rf.move(0);
    rb.move(0);

    pros::delay(500);

    intake_set(-100);
    pros::delay(900);
    intake_set(0);
}

}  // namespace

void autonomous() {
    const auton::Routine routine = auton::selected();
    const std::string name = auton::routine_name(routine);
    pros::lcd::set_text(6, "Auton: " + name);

    switch (routine) {
        case auton::Routine::kAllianceLeft:
        case auton::Routine::kAllianceRight:
        case auton::Routine::kFarSide:
            run_three_ball_routine();
            break;
        case auton::Routine::kSkills:
            run_three_ball_routine();
            pros::delay(250);
            run_three_ball_routine();
            break;
    }
}
