#include <algorithm>

#include <ccl/pid.hpp>

namespace ccl {

PID::PID() : kp(0.0), ki(0.0), kd(0.0) {}
PID::PID(double kp_, double ki_, double kd_) : kp(kp_), ki(ki_), kd(kd_) {}

double PID::update(double setpoint, double measurement, double dt) {
    double error = setpoint - measurement;

    double p_term = kp * error;

    total_error_ += error * dt;
    double i_term = ki * total_error_;

    double derivative = (error - prior_error_) / dt;
    double d_term = kd * derivative;

    prior_error_ = error;

    double output = p_term + i_term + d_term;

    return std::clamp(output, min_output, max_output);
}

void PID::reset() {
    total_error_ = 0.0;
    prior_error_ = 0.0;
}

} // namespace ccl