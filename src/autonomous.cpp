/**
 * Autonomous code section.
 * Runs automatically when the robot is in autonomous mode during a match.
 */

#include "main.h"

// Example autonomous routine
void autonomous() {
  pros::Motor left_front(1);
  pros::Motor right_front(2); // reverse one side

  left_front.move_relative(500, 100);   // move forward 500 ticks
  right_front.move_relative(500, 100);
  pros::delay(2000); // wait for 2 seconds

  left_front.move_relative(-500, 100);  // move back 500 ticks
  right_front.move_relative(-500, 100);
  pros::delay(2000);
}