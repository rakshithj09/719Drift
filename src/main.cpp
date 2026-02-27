#include "main.h"
#include "globals.h"
#include "autonomous.h"

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(0, "Init OK");
}

void disabled() {}

void competition_initialize() {
	// Allow driver to select alliance, side and routine before match
	run_auton_selector();
}
