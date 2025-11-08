#include "main.h"  

pros::Motor LF(1), LM(2), LB(3), RF(4), RM(5), RB(6);
pros::Motor front_bottom(7), front_top(9), back(8);

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
