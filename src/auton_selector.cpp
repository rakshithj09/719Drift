#include "main.h"
#include "autonomous.h"
#include "globals.h"

// Simple controller / LCD-based auton selector.
// Controls:
// - Left/Right: cycle color
// - Up/Down: cycle side
// - A: cycle routine
// - B: confirm selection (exit selector)

AllianceColor g_auton_color = AllianceColor::RED;
FieldSide g_auton_side = FieldSide::LEFT;
AutonRoutine g_auton_routine = AutonRoutine::SKILLS;

static const char* color_name(AllianceColor c) {
    return c == AllianceColor::RED ? "RED" : "BLUE";
}

static const char* side_name(FieldSide s) {
    return s == FieldSide::LEFT ? "LEFT" : "RIGHT";
}

static const char* routine_name(AutonRoutine r) {
    switch (r) {
        case AutonRoutine::SKILLS: return "SKILLS";
        case AutonRoutine::LEFT_LINEUP: return "LEFT_LINEUP";
        case AutonRoutine::RIGHT_LINEUP: return "RIGHT_LINEUP";
    }
    return "UNKNOWN";
}

void run_auton_selector() {
    pros::lcd::initialize();
    pros::lcd::set_text(0, "Auton selector");

    // Show instructions briefly
    pros::lcd::set_text(1, "L/R: Color  U/D: Side");
    pros::lcd::set_text(2, "A: Cycle routine");
    pros::lcd::set_text(3, "B: Confirm");

    bool confirmed = false;
    // Timeout after 90 seconds to avoid blocking indefinitely on field
    const int timeout_ms = 90000;
    int elapsed = 0;
    const int loop_delay = 100;

    bool prevLeft = false, prevRight = false, prevUp = false, prevDown = false, prevA = false, prevB = false;
    while (!confirmed && elapsed < timeout_ms) {
        // Update display
        std::string line1 = std::string("Color: ") + color_name(g_auton_color);
        std::string line2 = std::string("Side:  ") + side_name(g_auton_side);
        std::string line3 = std::string("Rout:  ") + routine_name(g_auton_routine);

        pros::lcd::set_text(1, line1.c_str());
        pros::lcd::set_text(2, line2.c_str());
        pros::lcd::set_text(3, line3.c_str());

        // Read controller
        // Manual edge detection for controller buttons (pros Controller doesn't provide get_digital_changed here)
        bool curLeft = master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);
        bool curRight = master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);
        bool curUp = master.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
        bool curDown = master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
        bool curA = master.get_digital(pros::E_CONTROLLER_DIGITAL_A);
        bool curB = master.get_digital(pros::E_CONTROLLER_DIGITAL_B);

        if (curLeft && !prevLeft) {
            g_auton_color = (g_auton_color == AllianceColor::RED) ? AllianceColor::BLUE : AllianceColor::RED;
        }
        if (curRight && !prevRight) {
            g_auton_color = (g_auton_color == AllianceColor::RED) ? AllianceColor::BLUE : AllianceColor::RED;
        }
        if (curUp && !prevUp) {
            g_auton_side = (g_auton_side == FieldSide::LEFT) ? FieldSide::RIGHT : FieldSide::LEFT;
        }
        if (curDown && !prevDown) {
            g_auton_side = (g_auton_side == FieldSide::LEFT) ? FieldSide::RIGHT : FieldSide::LEFT;
        }
        if (curA && !prevA) {
            int next = (static_cast<int>(g_auton_routine) + 1) % 3;
            g_auton_routine = static_cast<AutonRoutine>(next);
        }
        if (curB && !prevB) {
            confirmed = true;
            break;
        }

        prevLeft = curLeft; prevRight = curRight; prevUp = curUp; prevDown = curDown; prevA = curA; prevB = curB;

        pros::delay(loop_delay);
        elapsed += loop_delay;
    }

    // Final display line
    std::string final = std::string("Sel: ") + color_name(g_auton_color) + " " + side_name(g_auton_side) + " " + routine_name(g_auton_routine);
    pros::lcd::clear();
    pros::lcd::set_text(0, "Auton ready");
    pros::lcd::set_text(1, final.c_str());
}

AllianceColor get_auton_color() { return g_auton_color; }
FieldSide get_auton_side() { return g_auton_side; }
AutonRoutine get_auton_routine() { return g_auton_routine; }
