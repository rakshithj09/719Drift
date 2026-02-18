#pragma once

#include "pros/imu.hpp"
#include "pros/misc.hpp"
#include "pros/rotation.hpp"

#include <cstdint>

namespace odom {

struct Pose2D {
    double x{0.0};
    double y{0.0};
    double thetaDeg{0.0};
};

double normalizeDeg(double angleDeg);
double degToRad(double angleDeg);

class Odometry {
  public:
    Odometry(pros::Imu& imu,
             pros::Rotation& verticalSensor,
             pros::Rotation& horizontalSensor,
             double trackingWheelDiameterIn,
             double verticalGearRatio = 1.0,
             double horizontalGearRatio = 1.0,
             bool verticalReversed = false,
             bool horizontalReversed = false);

    void reset(double x, double y, double thetaDeg);
    void update();
    Pose2D pose() const;

  private:
    double ticksToDistance(int32_t ticks, bool horizontal) const;

    pros::Imu& imu_;
    pros::Rotation& verticalSensor_;
    pros::Rotation& horizontalSensor_;

    const double wheelCircumferenceIn_;
    const double verticalTicksToInches_;
    const double horizontalTicksToInches_;
    const double verticalSign_;
    const double horizontalSign_;

    Pose2D current_{};
    double lastVerticalDist_{0.0};
    double lastHorizontalDist_{0.0};
    mutable pros::Mutex poseMutex_;
};

constexpr int IMU_PORT = 20;
constexpr int VERTICAL_TRACKING_PORT = 8;
constexpr int HORIZONTAL_TRACKING_PORT = 9;

constexpr bool VERTICAL_TRACKING_REVERSED = false;
constexpr bool HORIZONTAL_TRACKING_REVERSED = false;

constexpr double TRACKING_WHEEL_DIAMETER_IN = 2.0;
constexpr double VERTICAL_TRACKING_GEAR_RATIO = 1.0;
constexpr double HORIZONTAL_TRACKING_GEAR_RATIO = 1.0;

extern pros::Imu imu;
extern pros::Rotation verticalTracker;
extern pros::Rotation horizontalTracker;
extern Odometry odometry;

void start_odometry_task();

}  // namespace odom
