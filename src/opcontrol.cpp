#include "main.h"
#include "globals.h"
#include "odometry.h"

#include <string>


void opcontrol() {
	pros::lcd::initialize();
	pros::lcd::set_text(0, "Opcontrol running");
	uint32_t lastPoseDisplay = 0;
	while (true) {
		drivetrain_control();
		intake_control();
		uint32_t now = pros::millis();
		if (now - lastPoseDisplay >= 100) {
			auto pose = odom::odometry.pose();
			pros::lcd::set_text(1, "X: " + std::to_string(pose.x));
			pros::lcd::set_text(2, "Y: " + std::to_string(pose.y));
			pros::lcd::set_text(3, "Th: " + std::to_string(pose.thetaDeg));
			lastPoseDisplay = now;
		}
		pros::delay(20);
	}
}
