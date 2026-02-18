#include "main.h"
#include "globals.h"
#include "auton_selector.h"

void opcontrol() {
	while (true) {
		drivetrain_control();
		intake_control();
		pros::delay(20);
	}
}
