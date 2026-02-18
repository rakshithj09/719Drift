#include "main.h"
#include "globals.h"
#include "odometry.h"

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(0, "Init OK");
	odom::imu.reset();
	while (odom::imu.is_calibrating()) {
		pros::delay(10);
	}
	odom::odometry.reset(0.0, 0.0, 0.0);
	odom::start_odometry_task();
}

void disabled() {}

void competition_initialize() {}
