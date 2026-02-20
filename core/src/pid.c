#include "ccl/pid.h"

void ccl_pid_init(
    ccl_pid_t *pid, 
    double kp, 
    double ki, 
    double kd,
    double min_output,
    double max_output
) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;

    pid->min_output = min_output;
    pid->max_output = max_output;

    // Internal variables
    pid->total_error = 0.0;
    pid->prior_error = 0.0;
}

double ccl_pid_update(
    ccl_pid_t *pid, 
    double setpoint, 
    double measurement, 
    double dt
) {
    // P
    double error = setpoint - measurement;
    double p_term = pid->kp * error;

    // I
    pid->total_error += error * dt;
    double i_term = pid->ki * pid->total_error;

    // D
    double d_term = 0.0;
    if (dt > 0.0) {
        d_term = pid->kd * (error - pid->prior_error) / dt;
    }

    pid->prior_error = error;

    double output = p_term + i_term + d_term;

    if (output < pid->min_output) {
        return pid->min_output;
    } else if (output > pid->max_output) {
        return pid->max_output;
    } else {
        return output;
    }
}

void ccl_pid_reset(ccl_pid_t *pid) {
    pid->total_error = 0.0;
    pid->prior_error = 0.0;
}