#pragma once

#include <limits>

namespace ccl {

class PID {
public:
    double kp;
    double ki;
    double kd;

    double min_output = -std::numeric_limits<double>::infinity();
    double max_output = std::numeric_limits<double>::infinity();

    PID();
    PID(double kp_, double ki_, double kd_);

    double update(double setpoint, double measurement, double dt);
    void reset();

private:
    double total_error_ = 0.0;
    double prior_error_ = 0.0;
};

} // namespace ccl