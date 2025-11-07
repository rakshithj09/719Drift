#include "main.h"

// Operator control
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	// Intake motors
	pros::Motor front_bottom(7);
	pros::Motor back(8);
	pros::Motor front_top(9);

	// Drive motors (same ports as main.cpp)
	pros::MotorGroup left_mg({1, 2, 3});
	pros::MotorGroup right_mg({-4, -5, -6}); // Negative here safely reverses the group

	while (true) {
		// --- Drivetrain (Arcade) ---
		int forward = master.get_analog(ANALOG_LEFT_Y);
		int turn = master.get_analog(ANALOG_RIGHT_X);
		int left_power = forward + turn;
		int right_power = forward - turn;
		left_mg.move(left_power);
		right_mg.move(right_power);

		// --- Intake control ---
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			// intake in
			front_bottom.move(127);
			front_top.move(127);
			back.move(-127);
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			// outtake
			front_bottom.move(-127);
			back.move(127);
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			// basket to middle
			front_bottom.move(-127);
			front_top.move(127);
			back.move(127);
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			// basket to top
			front_bottom.move(-127);
			front_top.move(-127);
			back.move(127);
		} else {
			// stop all
			front_bottom.move(0);
			front_top.move(0);
			back.move(0);
		}

		pros::delay(20);
	}
}