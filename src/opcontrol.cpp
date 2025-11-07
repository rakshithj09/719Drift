#include "main.h"

/**
 * Operator control (driver control) section.
 * Runs continuously when the robot is under manual control with the controller.
 */

// 
void opcontrol() {
	pros::adi::DigitalOut piston('A'); // replace 'A' with the port used on your brain
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor front_bottom(7);// blue motor
	pros::Motor back(8); // green motor
	pros::Motor front_top(9); // green motor


	pros::MotorGroup left_mg({1, -2, -3});
	pros::MotorGroup right_mg({-4, 5, 6});
	// Groups motors on the left and right sides so each group acts like one motor.
	// Replace the numbers with your actual motor ports.

	while (true) {
		pros::Controller master(pros::E_CONTROLLER_MASTER);
		/*bool pistonState = false;
	  
		// Toggle piston when button A is pressed
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
				pistonState = !pistonState;
				piston.set_value(pistonState);
			}
		  
			  pros::delay(20);

		pros::lcd::print(0, "%d %d %d",
		                 (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		// Displays which LCD buttons are pressed on line 0.
		// 0s and 1s show if left, center, or right buttons are currently pressed.
		// This is for testing; it’s not needed for driving.
		
		// 5 watt top is clockwise
		// 5 watt watt back clockwise
		// 11 watt counterclockwise

		// R2 into basket
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			front_bottom.move(127);
			front_top.move(127);
			back.move(-127);
		  }
		else {
			front_bottom.move(0);
			front_top.move(0);
			back.move(0);
		  }
		// L2 Outtake from basket to bottom goal
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			front_bottom.move(-127);
			back.move(127);
		  }
		else {
			front_bottom.move(0);
			back.move(0);
		  } 
		// R1 Basket to middle
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			front_bottom.move(-127);
			front_top.move(127);
			back.move(127);
		  }
		else {
			front_bottom.move(0);
			front_top.move(0);
			back.move(0);
		  }
		// L1 Basket to Top
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			front_bottom.move(-127);
			front_top.move(-127);
			back.move(127);
		  }
		else {
			front_bottom.move(0);
			front_top.move(0);
			back.move(0);
		  }
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
			left_mg.move(127);
			right_mg.move(-127);
			pros::delay(1000);
		}*/
		  
		  pros::delay(20);
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



