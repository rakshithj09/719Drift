/**
 * Autonomous code section.
 * Runs automatically when the robot is in autonomous mode during a match.
 */

 #include "main.h"
 #include "pros/motors.hpp"
 #include "pros/rtos.hpp"
 
 // These come from main.cpp. We reference them here without redefining.
 extern pros::Motor LF;
 extern pros::Motor LM;
 extern pros::Motor LB;
 extern pros::Motor RF;
 extern pros::Motor RM;
 extern pros::Motor RB;
 
 extern pros::Motor front_bottom;
 extern pros::Motor front_top;
 extern pros::Motor back;
 
 static constexpr int RIGHT_SIGN = -1; // match driver control, right side reversed

 static void drive_move(int left_power, int right_power) {
   LF.move(left_power);
   LM.move(left_power);
   LB.move(left_power);
 
   RF.move(RIGHT_SIGN * right_power);
   RM.move(RIGHT_SIGN * right_power);
   RB.move(RIGHT_SIGN * right_power);
 }
 
 static void drive_brake() {
   LF.brake(); LM.brake(); LB.brake();
   RF.brake(); RM.brake(); RB.brake();
 }
 
 // Intake helper
 static void intake_move(int bottom, int top, int rear) {
   front_bottom.move(bottom);
   front_top.move(top);
   back.move(rear);
 }
 
 void autonomous() {
   // Intake in
   intake_move(127, 127, -127);
 
   
   // Drive forward
   drive_move(100, 100);
   pros::delay(1200); //Tells the wheel motors to stop after 1.2 seconds
 
   // Stop everything
   drive_brake();
   intake_move(0, 0, 0);
 }