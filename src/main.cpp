#include "main.h"  

// Includes the PROS main library header. This gives access to all PROS functions and classes.

/**
 * A callback function for LLEMU's center button.
 * (LLEMU = Little LCD Emulator on the V5 Brain)
 * When this function is called, it toggles a message on line 2 of the Brain screen.
 */
void on_center_button() {
	static bool pressed = false; // Keeps track of whether the button was last pressed
	pressed = !pressed;          // Flips the value each time it's pressed
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");  // Show text on line 2
	} else {
		pros::lcd::clear_line(2);                  // Clear line 2 when pressed again
	}
}

/**
 * Runs initialization code.
 * This happens as soon as the robot program starts (before driver or autonomous).
 */
void initialize() {
	pros::lcd::initialize();                 // Starts up the V5 Brain LCD screen
	pros::lcd::set_text(1, "Hello PROS User!"); // Prints text on line 1

	pros::lcd::register_btn1_cb(on_center_button); 
	// Registers the callback so the center LCD button calls on_center_button()
}

/**
 * Runs while the robot is disabled (for example, between matches).
 */
void disabled() {}

/**
 * Runs after initialize() and before autonomous.
 * Used for competition setup (like choosing an autonomous routine on the screen).
 */
void competition_initialize() {}

/**
 * Autonomous code section.
 * Runs automatically when the robot is in autonomous mode during a match.
 */
void autonomous() {}

/**
 * Operator control (driver control) section.
 * Runs continuously when the robot is under manual control with the controller.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	// Creates a controller object for reading joysticks and button inputs.

	pros::MotorGroup left_mg({17, 18, 15});
	pros::MotorGroup right_mg({20, 6, 19});
	// Groups motors on the left and right sides so each group acts like one motor.
	// Replace the numbers with your actual motor ports.

	while (true) {
		// --- Optional Debug Display ---
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
		left_mg.move(left_power);
		right_mg.move(right_power);

		pros::delay(20); // Runs the loop every 20ms to keep things stable (50 times per second)
	}
}