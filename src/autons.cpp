#include "main.h"

const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;

void default_constants() {
  chassis.pid_drive_constants_set(20.0, 0.0, 100.0);
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);
  chassis.pid_turn_constants_set(3.0, 0.05, 20.0, 15.0);

  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  chassis.pid_angle_behavior_set(ez::shortest);
}

void drive_forward() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

void turn_right() {
  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

void drive_square() {
  for (int i = 0; i < 4; i++) {
    chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_set(90_deg, TURN_SPEED);
    chassis.pid_wait();
  }
}
