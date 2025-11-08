#include "main.h"


/**
* Operator control (driver control) section.
* Runs continuously when the robot is under manual control with the controller.
*/


//
void opcontrol() {
   pros::adi::DigitalOut piston('A'); // replace 'A' with the port used on your brain
  
   pros::Controller master(pros::E_CONTROLLER_MASTER);
   pros::Motor front_bottom(7, pros::v5::MotorGears::blue,pros::v5::MotorUnits::degrees); // blue motor w/ degrees
   pros::Motor back(8, pros::v5::MotorGears::green,pros::v5::MotorUnits::degrees); // green motor w/ degrees
   pros::Motor front_top(9, pros::v5::MotorGears::green,pros::v5::MotorUnits::degrees); // green motor w/ degrees
   pros::IMU imu_sensor(10); // IMU sensor on port 10
   while (imu_sensor.is_calibrating()) {
       pros::delay(20);
    }


   pros::MotorGroup left_mg({1, -2, -3});
   pros::MotorGroup right_mg({-4, 5, 6});
   left_mg.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
   right_mg.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
   // Groups motors on the left and right sides so each group acts like one motor.
   // Replace the numbers with your actual motor ports.


   bool pistonState = false;
   bool autoTurnActive = false;

   // Drift control
   double kP = 1.3; // Adjust var(small-inaccurate; large-oscillates)
   imu_sensor.tare_rotation(); // Sets current heading to 0 degrees


   while (true) {
       if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
           autoTurnActive = true;
           imu_sensor.tare_rotation();
       }


       if (autoTurnActive) {
           const double target_degrees = 90.0;
           if (imu_sensor.get_rotation() < target_degrees) {
               left_mg.move(127);
               right_mg.move(-127);
           } else {
               left_mg.move(0);
               right_mg.move(0);
               autoTurnActive = false;
               imu_sensor.tare_rotation();
           }
       }

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
       // Top Outtake
       if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
       front_bottom.move(-127);
       back.move(127);
       front_top.move(-127);
       }
       // Middle Outtake
       else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
       front_bottom.move(-127);
       back.move(127);
       front_top.move(127);
       }

       // Bottom Outtake
       else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
       front_bottom.move(127);
       back.move(127);
       }
       // Basket Intake
       else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
       front_bottom.move(-100);
       back.move(-127);
       }
       else{
           front_bottom.move(0);
           front_top.move(0);
           back.move(0);
       }
        
         pros::delay(20);
               // --- Joystick control setup (Arcade Drive) ---
       int forward = master.get_analog(ANALOG_LEFT_Y); // Right joystick up/down controls forward & backward
       int turn = master.get_analog(ANALOG_RIGHT_X);     // Left joystick left/right controls turning
       //Reduce base speed to 0.8
       double speedScale = 0.8;
       // Combine joystick inputs to control the drivetrain
       int left_power = (forward + turn)*speedScale;   // Left side motors get more power when turning right
       int right_power = (forward - turn)*speedScale;  // Right side motors get more power when turning left


       // Move motor groups based on joystick input unless auto turn is running
       if (!autoTurnActive) {
        // IMU Rotation
        double current_heading = imu_sensor.get_rotation();
        double heading_error = 0-current_heading;
        double correction = kP * heading_error;
        if (abs(turn) < 10 && abs(forward) > 10) {
            left_mg.move(forward + correction);
            right_mg.move(forward - correction);
        }
        else {
            left_mg.move(forward + turn);
            right_mg.move(forward - turn);
            imu_sensor.tare_rotation();
       }


       pros::delay(20); // Runs the loop every 20ms to keep things stable (50 times per second)
       }
    }
}