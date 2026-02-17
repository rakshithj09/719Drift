#include "main.h"
#include "globals.h"

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(0, "Init OK");
}

void disabled() {}

void competition_initialize() {}