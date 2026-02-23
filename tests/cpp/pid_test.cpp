#include <gtest/gtest.h>

#include <ccl/pid.hpp>

TEST(PIDTest, DefaultConstructorZeroGains) {
    ccl::PID pid;
    EXPECT_EQ(pid.get_kp(), 0.0);
    EXPECT_EQ(pid.get_ki(), 0.0);
    EXPECT_EQ(pid.get_kd(), 0.0);
}

TEST(PIDTest, POnlyReturnsKpTimesError) {
    ccl::PID pid(2.0, 0.0, 0.0);
    double output = pid.update(10.0, 0.0, 0.1);
    EXPECT_DOUBLE_EQ(output, 20.0);
}

TEST(PIDTest, OutputClampedToMin) {
    ccl::PID pid(1.0, 0.0, 0.0);
    pid.set_min_output(-1.5);
    double output = pid.update(-10.0, 0.0, 0.1);
    EXPECT_DOUBLE_EQ(output, pid.get_min_output());
}

TEST(PIDTest, OutputClampedToMax) {
    ccl::PID pid(1.0, 0.0, 0.0);
    pid.set_max_output(1.5);
    double output = pid.update(10.0, 0.0, 0.1);
    EXPECT_DOUBLE_EQ(output, pid.get_max_output());
}

TEST(PIDTest, ResetClearsIntegral) {
    ccl::PID pid(0.0, 1.0, 0.0);
    double output = pid.update(10.0, 0.0, 0.1);
    EXPECT_GT(output, 0.0);

    pid.reset();
    output = pid.update(0.0, 0.0, 0.1);
    EXPECT_DOUBLE_EQ(output, 0.0);
}