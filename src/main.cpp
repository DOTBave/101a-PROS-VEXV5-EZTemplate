#include "main.h"

// Update these values to match the robot.
ez::Drive chassis(
    {1},        // Left drive port
    {-2},       // Right drive port (negative reverses the motor)
    11,          // IMU port
    3.25,      // Drive wheel diameter in inches
    200);       // Motor cartridge RPM

void initialize() {
  ez::ez_template_print();
  pros::delay(500);

  default_constants();

  ez::as::auton_selector.autons_add({
      {"Drive Forward\n\nDrive forward and back", drive_forward},
      {"Turn Right\n\nTurn 90 degrees", turn_right},
      {"Square\n\nDrive in a square", drive_square},
  });

  chassis.initialize();
  ez::as::initialize();
  master.rumble(chassis.drive_imu_calibrated() ? "." : "---");
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
  chassis.pid_targets_reset();
  chassis.drive_imu_reset();
  chassis.drive_sensor_reset();
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);

  ez::as::auton_selector.selected_auton_call();
}

void opcontrol() {
  chassis.drive_brake_set(MOTOR_BRAKE_COAST);

  while (true) {
    // this if statement ensures that the autonomous selector can only be used when the robot is not connected to the field control system
    // if macros get called during the driver control period, it's an automatic DQ!!
    if (!pros::competition::is_connected()) {
      // these if statements allows the user to page up and down through the autonomous selector
      // and select an autonomous with the A button
      if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
        ez::as::page_down();
      } else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        ez::as::page_up();
      }
      else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        autonomous();
        chassis.drive_brake_set(MOTOR_BRAKE_COAST);
      }
    }
    // chassis.opcontrol_tank(); // this is for tank control
    chassis.opcontrol_arcade_standard(ez::SINGLE); // this is for arcade control
    pros::delay(ez::util::DELAY_TIME);
  }
}
