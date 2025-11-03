#include "main.cpp"
/**
 * Operator control (driver control) section.
 * Runs continuously when the robot is under manual control with the controller.
 */

 void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor intake11W(8, pros::v5::MotorGears::blue);
	pros::Motor intake5W_1(9, pros::v5::MotorGears::blue);
	pros::Motor intake5W_2(10, pros::v5::MotorGears::blue);
	pros::MotorGroup intake5W({9, 10});
	// Creates a controller object for reading joysticks and button inputs.

	pros::MotorGroup left_mg({17, 18, 15});
	pros::MotorGroup right_mg({20, 6, 19});
	// Groups motors on the left and right sides so each group acts like one motor.
	// Replace the numbers with your actual motor ports.

	while (true) {
		// --- Optional Debug Display --
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			intake5W.move(127);
		  }
		  // Top Outtake
		  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			intake5W_1.move(-127);
			intake5W_2.move(127);
			intake11W.move(127);
		  }
		  // Middle Outtake
		  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
			intake5W_1.move(-127);
			intake5W_2.move(127);
			intake11W.move(-127);
		  }
	  
		  // Bottom Output
		  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			intake5W.move(-127);
		  } 
		  
		  pros::delay(20);
		}
		pros::lcd::print(0, "%d %d %d",
		                 (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		// Displays which LCD buttons are pressed on line 0.
		// 0s and 1s show if left, center, or right buttons are currently pressed.
		// This is for testing; it’s not needed for driving.

		// --- Joystick control setup (Arcade Drive) ---
		int forward = master.get_analog(ANALOG_RIGHT_Y); // Right joystick up/down controls forward & backward
		int turn = master.get_analog(ANALOG_LEFT_X);     // Left joystick left/right controls turning

		// Combine joystick inputs to control the drivetrain
		int left_power = forward + turn;   // Left side motors get more power when turning right
		int right_power = forward - turn;  // Right side motors get more power when turning left

		// Move motor groups based on joystick input
		left_mg.move(127);
		right_mg.move(127);

		pros::delay(20); // Runs the loop every 20ms to keep things stable (50 times per second)
}

