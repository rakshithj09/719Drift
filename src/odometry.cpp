#include "odometry.h"

#include <cmath>
#include <memory>

#include "pros/rtos.hpp"

namespace {
constexpr double kPi = 3.14159265358979323846;
constexpr double kCentidegreesPerRotation = 360.0 * 100.0;
constexpr int kUpdateDelayMs = 10;

std::unique_ptr<pros::Task> g_odometryTask;

void odometry_task_fn(void*) {
    while (true) {
        odom::odometry.update();
        pros::delay(kUpdateDelayMs);
    }
}
}  // namespace

namespace odom {

pros::Imu imu(IMU_PORT);
pros::Rotation verticalTracker(VERTICAL_TRACKING_REVERSED ? -VERTICAL_TRACKING_PORT : VERTICAL_TRACKING_PORT);
pros::Rotation horizontalTracker(HORIZONTAL_TRACKING_REVERSED ? -HORIZONTAL_TRACKING_PORT : HORIZONTAL_TRACKING_PORT);

Odometry odometry(imu, verticalTracker, horizontalTracker, TRACKING_WHEEL_DIAMETER_IN, VERTICAL_TRACKING_GEAR_RATIO, HORIZONTAL_TRACKING_GEAR_RATIO, VERTICAL_TRACKING_REVERSED, HORIZONTAL_TRACKING_REVERSED);

double normalizeDeg(double angleDeg) {
    double wrapped = std::fmod(angleDeg, 360.0);
    if (wrapped > 180.0) wrapped -= 360.0;
    if (wrapped <= -180.0) wrapped += 360.0;
    return wrapped;
}

double degToRad(double angleDeg) {
    return angleDeg * kPi / 180.0;
}

Odometry::Odometry(pros::Imu& imu,
                   pros::Rotation& verticalSensor,
                   pros::Rotation& horizontalSensor,
                   double trackingWheelDiameterIn,
                   double verticalGearRatio,
                   double horizontalGearRatio,
                   bool verticalReversed,
                   bool horizontalReversed)
    : imu_(imu),
      verticalSensor_(verticalSensor),
      horizontalSensor_(horizontalSensor),
      wheelCircumferenceIn_(trackingWheelDiameterIn * kPi),
      verticalTicksToInches_(wheelCircumferenceIn_ / (verticalGearRatio * kCentidegreesPerRotation)),
      horizontalTicksToInches_(wheelCircumferenceIn_ / (horizontalGearRatio * kCentidegreesPerRotation)),
      verticalSign_(verticalReversed ? -1.0 : 1.0),
      horizontalSign_(horizontalReversed ? -1.0 : 1.0) {
    reset(0.0, 0.0, 0.0);
}

double Odometry::ticksToDistance(int32_t ticks, bool horizontal) const {
    const double conversion = horizontal ? horizontalTicksToInches_ : verticalTicksToInches_;
    const double sign = horizontal ? horizontalSign_ : verticalSign_;
    return static_cast<double>(ticks) * conversion * sign;
}

void Odometry::reset(double x, double y, double thetaDeg) {
    verticalSensor_.reset_position();
    horizontalSensor_.reset_position();
    lastVerticalDist_ = 0.0;
    lastHorizontalDist_ = 0.0;

    poseMutex_.take(TIMEOUT_MAX);
    current_.x = x;
    current_.y = y;
    current_.thetaDeg = normalizeDeg(thetaDeg);
    poseMutex_.give();
}

void Odometry::update() {
    const double verticalDist = ticksToDistance(verticalSensor_.get_position(), false);
    const double horizontalDist = ticksToDistance(horizontalSensor_.get_position(), true);

    const double deltaVertical = verticalDist - lastVerticalDist_;
    const double deltaHorizontal = horizontalDist - lastHorizontalDist_;
    lastVerticalDist_ = verticalDist;
    lastHorizontalDist_ = horizontalDist;

    const double headingDeg = normalizeDeg(imu_.get_heading());
    const double headingRad = degToRad(headingDeg);

    const double deltaX = deltaVertical * std::cos(headingRad) - deltaHorizontal * std::sin(headingRad);
    const double deltaY = deltaVertical * std::sin(headingRad) + deltaHorizontal * std::cos(headingRad);

    poseMutex_.take(TIMEOUT_MAX);
    current_.x += deltaX;
    current_.y += deltaY;
    current_.thetaDeg = headingDeg;
    poseMutex_.give();
}

Pose2D Odometry::pose() const {
    poseMutex_.take(TIMEOUT_MAX);
    Pose2D copy = current_;
    poseMutex_.give();
    return copy;
}

void start_odometry_task() {
    if (g_odometryTask) {
        return;
    }

    g_odometryTask = std::make_unique<pros::Task>(
        odometry_task_fn, nullptr, TASK_PRIORITY_DEFAULT + 1, TASK_STACK_DEPTH_DEFAULT, "odom");
}

}  // namespace odom
