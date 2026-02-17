#include "main.h"
#include "globals.h"


void opcontrol() {
	pros::lcd::initialize();
	pros::lcd::set_text(0, "Opcontrol running");
	while (true) {
		drivetrain_control();
		intake_control();
		pros::delay(20);
	}
}