#include "main.h"

/**
 * Operator control (driver control) section.
 * Runs continuously when the robot is under manual control with the controller.
 */

// 
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	


	pros::MotorGroup left_mg({1, -2, -3});
	pros::MotorGroup right_mg({-4, 5, 6});
	// Groups motors on the left and right sides so each group acts like one motor.
	// Replace the numbers with your actual motor ports.

	while (true) {


		pros::lcd::print(0, "%d %d %d",
		                 (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		// Displays which LCD buttons are pressed on line 0.
		// 0s and 1s show if left, center, or right buttons are currently pressed.
		// This is for testing; it’s not needed for driving.

		// --- Joystick control setup (Arcade Drive) ---
		int forward = master.get_analog(ANALOG_LEFT_Y); // Right joystick up/down controls forward & backward
		int turn = master.get_analog(ANALOG_RIGHT_X);     // Left joystick left/right controls turning

		// Combine joystick inputs to control the drivetrain
		int left_power = forward + turn;   // Left side motors get more power when turning right
		int right_power = forward - turn;  // Right side motors get more power when turning left

		// Move motor groups based on joystick input
		left_mg.move(left_power*.9);
		right_mg.move(right_power);

		pros::delay(20); // Runs the loop every 20ms to keep things stable (50 times per second)
	}
}
