#pragma once

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "EZ-Template/api.hpp"

#include "autons.hpp"
#include "subsystems.hpp"

using namespace okapi::literals;

extern "C" {
void initialize(void);
void disabled(void);
void competition_initialize(void);
void autonomous(void);
void opcontrol(void);
}
