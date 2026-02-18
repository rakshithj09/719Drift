#include "auton_selector.h"

#include "pros/llemu.hpp"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"

#include <array>
#include <cmath>
#include <memory>
#include <string>

namespace {
constexpr std::array<const char*, 4> kRoutineNames = {
    "Alliance Left",
    "Alliance Right",
    "Far Side Rush",
    "Driver Skills",
};

int currentIndex = 0;
pros::Mutex selectionMutex;

std::unique_ptr<pros::Task> dashboardTask;
pros::Mutex statusMutex;
std::string statusLine = "Ready";

pros::Mutex timerMutex;
uint32_t timerResetMs = 0;

std::string format_double(double value, int precision = 1) {
    const int scaled = static_cast<int>(std::round(value * std::pow(10, precision)));
    std::string str = std::to_string(scaled);
    if (precision == 0) {
        return str;
    }
    const bool isNegative = str[0] == '-';
    const size_t offset = isNegative ? 1 : 0;
    while (str.size() - offset <= static_cast<size_t>(precision)) {
        str.insert(offset, "0");
    }
    str.insert(str.end() - precision, '.');
    return str;
}

void draw_dashboard() {
    const double batteryPct = pros::battery::get_capacity();
    const double batteryVoltage = pros::battery::get_voltage() / 1000.0;
    const double batteryTemp = pros::battery::get_temperature();

    timerMutex.take(TIMEOUT_MAX);
    const double elapsed = (pros::millis() - timerResetMs) / 1000.0;
    timerMutex.give();

    selectionMutex.take(TIMEOUT_MAX);
    const std::string autonName = kRoutineNames[currentIndex];
    selectionMutex.give();

    statusMutex.take(TIMEOUT_MAX);
    const std::string statusCopy = statusLine;
    statusMutex.give();

    pros::lcd::set_text(0, "719D Brain HUD");
    pros::lcd::set_text(1, "Batt: " + format_double(batteryPct, 1) + "%  " + format_double(batteryVoltage, 2) + "V  " + format_double(batteryTemp, 1) + "C");
    pros::lcd::set_text(2, "Match Timer: " + format_double(elapsed, 1) + "s");
    pros::lcd::set_text(3, "Selected Auton:");
    pros::lcd::set_text(4, "  > " + autonName);
    pros::lcd::set_text(5, "Buttons - L/R: select  C: reset timer");
    pros::lcd::set_text(6, "Status: " + statusCopy);
    pros::lcd::set_text(7, "Ready to compete!");
}

void dashboard_task(void*) {
    while (true) {
        draw_dashboard();
        pros::delay(120);
    }
}

void on_left() {
    auton::select_previous();
}

void on_right() {
    auton::select_next();
}

void reset_timer() {
    timerMutex.take(TIMEOUT_MAX);
    timerResetMs = pros::millis();
    timerMutex.give();
}

void set_status(const std::string& text) {
    statusMutex.take(TIMEOUT_MAX);
    statusLine = text;
    statusMutex.give();
}

}  // namespace

namespace auton {

void initialize_brain_ui() {
    static bool initialized = false;
    if (!initialized) {
        pros::lcd::initialize();
        timerResetMs = pros::millis();
        pros::lcd::register_btn0_cb(on_left);
        pros::lcd::register_btn1_cb([]() {
            reset_timer();
            set_status("Match timer reset");
        });
        pros::lcd::register_btn2_cb(on_right);
        dashboardTask = std::make_unique<pros::Task>(dashboard_task, nullptr, TASK_PRIORITY_DEFAULT + 1, TASK_STACK_DEPTH_DEFAULT, "dashboard");
        initialized = true;
    }
    draw_dashboard();
}

void select_next() {
    selectionMutex.take(TIMEOUT_MAX);
    currentIndex = (currentIndex + 1) % kRoutineNames.size();
    const std::string name = kRoutineNames[currentIndex];
    selectionMutex.give();
    set_status("Auton -> " + name);
}

void select_previous() {
    selectionMutex.take(TIMEOUT_MAX);
    currentIndex = (currentIndex - 1 + kRoutineNames.size()) % kRoutineNames.size();
    const std::string name = kRoutineNames[currentIndex];
    selectionMutex.give();
    set_status("Auton -> " + name);
}

Routine selected() {
    selectionMutex.take(TIMEOUT_MAX);
    const int idx = currentIndex;
    selectionMutex.give();
    return static_cast<Routine>(idx);
}

const char* routine_name(Routine routine) {
    const int idx = static_cast<int>(routine);
    if (idx < 0 || idx >= static_cast<int>(kRoutineNames.size())) {
        return "Unknown";
    }
    return kRoutineNames[idx];
}

}  // namespace auton
