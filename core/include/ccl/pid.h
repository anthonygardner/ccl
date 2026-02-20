typedef struct {
    double kp;
    double ki;
    double kd;

    double min_output;
    double max_output;

    // Internal states
    double total_error;
    double prior_error;
} ccl_pid_t;

void ccl_pid_init(
    ccl_pid_t *pid, 
    double kp, 
    double ki, 
    double kd,
    double min_output,
    double max_output
);

double ccl_pid_update(
    ccl_pid_t *pid, 
    double setpoint, 
    double measurement, 
    double dt
);

void ccl_pid_reset(ccl_pid_t *pid);