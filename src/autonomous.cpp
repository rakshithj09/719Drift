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
 
// Tunables
static constexpr int DRIVE_POWER = 100;     // 0..127
static constexpr int DRIVE_TIME_MS = 1200;  // how long to drive
static constexpr int INTAKE_BTM = 127;      // intake in
static constexpr int INTAKE_TOP = 127;
static constexpr int INTAKE_REAR = -127;

// Drive helper that matches opcontrol MotorGroup signs
static void drive_move_forward(int power) {
  // left:  {1, -2, -3}
  LF.move( power);
  LM.move(-power);
  LB.move(-power);

  // right: {-4, 5, 6}
  RF.move(-power);
  RM.move( power);
  RB.move( power);
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
    // start intake and drive at the same time
    intake_move(INTAKE_BTM, INTAKE_TOP, INTAKE_REAR);
    drive_move_forward(DRIVE_POWER);
  
    pros::delay(DRIVE_TIME_MS);
  
    // stop
    drive_brake();
    intake_move(0, 0, 0);
  }