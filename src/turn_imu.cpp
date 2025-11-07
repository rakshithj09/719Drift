#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"
#include <cmath>

// ---------- helpers ----------
static double clamp(double x, double lo, double hi) {
  if (x < lo) return lo;
  if (x > hi) return hi;
  return x;
}

static double wrap180(double deg) {
  // returns angle in [-180, 180)
  while (deg >= 180.0) deg -= 360.0;
  while (deg <  -180.0) deg += 360.0;
  return deg;
}

static double wrap360(double deg) {
  // returns angle in [0, 360)
  while (deg >= 360.0) deg -= 360.0;
  while (deg <    0.0) deg += 360.0;
  return deg;
}

static void driveTank(pros::Motor* side[], int n, int millivolts) {
  for (int i = 0; i < n; i++) {
    if (side[i]) side[i]->move_voltage(millivolts);
  }
}

// ---------- core turn ----------
/*
  imu              your IMU object (already installed and calibrated)
  left[], right[]  arrays of pointers to your left and right drive motors
  left_n, right_n  counts in each array
  delta_deg        +90 for right turn, -90 for left turn, etc.
*/
void turn_by_deg(pros::Imu& imu,
                 pros::Motor* left[],  int left_n,
                 pros::Motor* right[], int right_n,
                 double delta_deg) {

  // gains and limits
  const double kP = 90.0;           // mv per degree of error
  const int max_mv = 9000;          // cap output
  const int min_mv = 2000;          // minimum to overcome friction
  const double settle_deg = 1.5;    // stop when within this error
  const int settle_time_ms = 200;   // hold inside window for this long
  const int timeout_ms = 2500;      // safety timeout
  const int dt = 10;                // loop delay ms

  // read start and compute target
  double start = imu.get_heading();            // 0..360
  double target = wrap360(start + delta_deg);  // 0..360

  int settled_ms = 0;
  int elapsed = 0;

  while (elapsed < timeout_ms) {
    double now = imu.get_heading();            // 0..360
    double err = wrap180(target - now);        // shortest path

    // compute mv. sign controls turn direction
    double out = kP * err;
    int mv = (int)clamp(out, -max_mv, max_mv);

    // apply minimum output when moving
    if (std::fabs(err) > settle_deg) {
      if (std::abs(mv) < min_mv) {
        mv = (mv >= 0) ? min_mv : -min_mv;
      }
    }

    // tank turn: left forward, right backward for positive mv
    driveTank(left,  left_n,  mv);
    driveTank(right, right_n, -mv);

    // check settle
    if (std::fabs(err) <= settle_deg) {
      settled_ms += dt;
      if (settled_ms >= settle_time_ms) break;
    } else {
      settled_ms = 0;
    }

    pros::delay(dt);
    elapsed += dt;
  }

  // stop
  driveTank(left,  left_n, 0);
  driveTank(right, right_n, 0);
}

// ---------- convenience wrappers ----------
void turn_right_90(pros::Imu& imu,
                   pros::Motor* left[], int left_n,
                   pros::Motor* right[], int right_n) {
  turn_by_deg(imu, left, left_n, right, right_n, +90.0);
}

void turn_left_90(pros::Imu& imu,
                  pros::Motor* left[], int left_n,
                  pros::Motor* right[], int right_n) {
  turn_by_deg(imu, left, left_n, right, right_n, -90.0);
}

/*
Example wiring in your main.cpp:

// make motors
pros::Motor LF(1, pros::E_MOTOR_GEAR_BLUE, false);
pros::Motor LB(2, pros::E_MOTOR_GEAR_BLUE, false);
pros::Motor RF(3, pros::E_MOTOR_GEAR_BLUE, true);
pros::Motor RB(4, pros::E_MOTOR_GEAR_BLUE, true);

// make IMU
pros::Imu IMU(5);

void initialize() {
  pros::delay(500);
  IMU.reset();
  while (IMU.is_calibrating()) pros::delay(20);
}

// build arrays of pointers
pros::Motor* LEFT[]  = { &LF, &LB };
pros::Motor* RIGHT[] = { &RF, &RB };

void autonomous() {
  // turn right 90 degrees
  turn_right_90(IMU, LEFT, 2, RIGHT, 2);

  // or turn left 90 degrees
  // turn_left_90(IMU, LEFT, 2, RIGHT, 2);

  // or any custom angle
  // turn_by_deg(IMU, LEFT, 2, RIGHT, 2, 135.0);
}
*/