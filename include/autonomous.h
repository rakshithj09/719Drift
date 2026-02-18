#pragma once
#include "main.h"

enum class AllianceColor { RED = 0, BLUE = 1 };
enum class FieldSide { LEFT = 0, RIGHT = 1 };
enum class AutonRoutine { SKILLS = 0, LEFT_LINEUP = 1, RIGHT_LINEUP = 2 };

// Current selection (set by selector UI)
extern AllianceColor g_auton_color;
extern FieldSide g_auton_side;
extern AutonRoutine g_auton_routine;

// Run a selector UI (blocks until user confirms selection or timeout)
void run_auton_selector();

// Getter helpers
AllianceColor get_auton_color();
FieldSide get_auton_side();
AutonRoutine get_auton_routine();
