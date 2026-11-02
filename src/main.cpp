#include "main.h"

// Update these values to match the robot.
ez::Drive chassis(
    {1, 2},     // Left drive ports
    {-3, -4},   // Right drive ports (negative reverses the motor)
    5,          // IMU port
    4.125,      // Drive wheel diameter in inches
    200);       // Drive wheel RPM

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
    chassis.opcontrol_tank();
    pros::delay(ez::util::DELAY_TIME);
  }
}
