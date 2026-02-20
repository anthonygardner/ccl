#include "utest.h"
#include "ccl/pid.h"

UTEST(pid, proportional_only) {
    ccl_pid_t pid;

    ccl_pid_init(&pid, 1.0, 0.0, 0.0, 0.0, 100.0);

    double output = ccl_pid_update(&pid, 100.0, 0.0, 0.1);

    ASSERT_NEAR(output, 100.0, 0.001);
}