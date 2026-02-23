#include <algorithm>

#include "ccl/pid.hpp"

namespace ccl {

PID::PID() {
    ccl_pid_init(&pid_, 0.0, 0.0, 0.0, -INFINITY, INFINITY);
}

PID::PID(double kp, double ki, double kd) {
    ccl_pid_init(&pid_, kp, ki, kd, -INFINITY, INFINITY);
}

double PID::update(double setpoint, double measurement, double dt) {
    double output = ccl_pid_update(&pid_, setpoint, measurement, dt);
    return std::clamp(output, pid_.min_output, pid_.max_output);
}

void PID::reset() {
    ccl_pid_reset(&pid_);
}

} // namespace ccl