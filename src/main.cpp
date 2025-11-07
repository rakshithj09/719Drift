#include "main.h"
#include "pros/imu.hpp"
#include "pros/motors.hpp"
#include <cmath>
#include <algorithm>

// --- DO NOT include turn_imu.cpp here ---
// The file turn_imu.cpp should be compiled separately.
// We just declare the functions we call (prototypes) and link to them.
void turn_by_deg(pros::Imu& imu,
                 pros::Motor* left[],  int left_n,
                 pros::Motor* right[], int right_n,
                 double delta_deg);
void turn_right_90(pros::Imu& imu,
                   pros::Motor* left[], int left_n,
                   pros::Motor* right[], int right_n);
void turn_left_90(pros::Imu& imu,
                  pros::Motor* left[], int left_n,
                  pros::Motor* right[], int right_n);

// ---------------------------
// Device setup (UPDATE PORTS TO MATCH YOUR WIRING)
// ---------------------------
pros::Controller master(pros::E_CONTROLLER_MASTER);

// Use simplest constructors (port only); configure in initialize()
pros::Motor LF(1);
pros::Motor LM(2);
pros::Motor LB(3);
pros::Motor RF(4);
pros::Motor RM(5);
pros::Motor RB(6);

// Intake / mechanism motors (keep your ports)
pros::Motor front_bottom(7);
pros::Motor back(8);
pros::Motor front_top(9);

// IMU
pros::Imu imu(10);  // <-- change to your actual IMU smart port

// Pointer arrays for IMU turn helpers
pros::Motor* LEFT[]  = { &LF, &LM, &LB };
pros::Motor* RIGHT[] = { &RF, &RM, &RB };

// ---------------------------
// Initialization
// ---------------------------
void on_center_button() {
  static bool pressed = false;
  pressed = !pressed;
  if (pressed) pros::lcd::set_text(2, "I was pressed!");
  else pros::lcd::clear_line(2);
}

static void configure_motors() {
  // Drive motors common config
  for (pros::Motor* m : LEFT) {
    m->set_gearing(pros::E_MOTOR_GEARSET_06);              // blue
    m->set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
    m->set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    m->set_reversed(false);                                 // left side forward
  }
  for (pros::Motor* m : RIGHT) {
    m->set_gearing(pros::E_MOTOR_GEARSET_06);
    m->set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
    m->set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    m->set_reversed(true);                                  // right side reversed for forward = forward
  }

  // Intake config
  for (pros::Motor* m : { &front_bottom, &front_top, &back }) {
    m->set_gearing(pros::E_MOTOR_GEARSET_06);
    m->set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  }
  // Flip if your intake fights itself
  front_bottom.set_reversed(false);
  front_top.set_reversed(false);
  back.set_reversed(true);
}

void initialize() {
  pros::lcd::initialize();
  pros::lcd::set_text(1, "719D — PROS");

  configure_motors();

  // Calibrate IMU
  imu.reset();
  pros::lcd::set_text(2, "Calibrating IMU...");
  while (imu.is_calibrating()) pros::delay(20);
  pros::lcd::set_text(2, "IMU Ready!");
}

void disabled() {}
void competition_initialize() {}

// ---------------------------
// Autonomous
// ---------------------------
void autonomous() {
  // Drive forward
  for (pros::Motor* m : LEFT)  m->move(100);
  for (pros::Motor* m : RIGHT) m->move(100);
  pros::delay(800);
  for (pros::Motor* m : LEFT)  m->brake();
  for (pros::Motor* m : RIGHT) m->brake();

  // Turn right 90° using IMU
  turn_right_90(imu, LEFT, 3, RIGHT, 3);

  // Drive backward
  for (pros::Motor* m : LEFT)  m->move(-100);
  for (pros::Motor* m : RIGHT) m->move(-100);
  pros::delay(500);
  for (pros::Motor* m : LEFT)  m->brake();
  for (pros::Motor* m : RIGHT) m->brake();
}