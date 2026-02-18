#pragma once

#include <string>

namespace auton {

enum class Routine {
    kAllianceLeft = 0,
    kAllianceRight,
    kFarSide,
    kSkills,
};

void initialize_brain_ui();
void select_next();
void select_previous();
Routine selected();
const char* routine_name(Routine routine);

}  // namespace auton
