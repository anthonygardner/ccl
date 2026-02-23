#pragma once

#include <cmath>
#include <limits>

extern "C" {
    #include "ccl/pid.h"
}

namespace ccl {

class PID {
public:
    PID();
    PID(double kp, double ki, double kd);

    double update(double setpoint, double measurement, double dt);
    void reset();

    double get_kp() const { return pid_.kp; }
    void set_kp(double kp) { pid_.kp = kp; }

    double get_ki() const { return pid_.ki; }
    void set_ki(double ki) { pid_.ki = ki; }

    double get_kd() const { return pid_.kd; }
    void set_kd(double kd) { pid_.kd = kd; }

    double get_min_output() const { return pid_.min_output; }
    void set_min_output(double min_output) { pid_.min_output = min_output; }

    double get_max_output() const { return pid_.max_output; }
    void set_max_output(double max_output) { pid_.max_output = max_output; }

private:
    ccl_pid_t pid_;
};

} // namespace ccl