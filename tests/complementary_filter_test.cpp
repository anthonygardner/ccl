#include <gtest/gtest.h>

#include <ccl/complementary_filter.hpp>

TEST(ComplementaryFilterTest, DefaultConstructor) {
    EXPECT_NO_THROW(ccl::ComplementaryFilter filter(1.0f, 0.1f));
}

TEST(ComplementaryFilterTest, TimeConstantGetter) {
    ccl::ComplementaryFilter filter(0.2f, 1.0f);

    float tc = filter.time_constant();
    EXPECT_EQ(tc, 0.25f);
}

TEST(ComplementaryFilterTest, UpdateConvergesWithZeroAngularRate) {
    ccl::ComplementaryFilter filter(0.98f, 0.1f);  // Trust the gyro

    float target_angle = 1.0f;
    float gyro_rate = 0.0f;

    for (int i = 0; i < 1000; i++) {
        filter.update(target_angle, gyro_rate);
    }

    EXPECT_NEAR(filter.angle(), target_angle, 0.01f);
}

TEST(ComplementaryFilterTest, UpdateDivergesWithNonzeroAngularRate) {
    ccl::ComplementaryFilter filter(0.98f, 0.1f);  // Trust the gyro

    float target_angle = 0.0f;
    float gyro_rate = 1.0f;

    for (int i = 0; i < 500; i++) {
        float angle = filter.update(target_angle, gyro_rate);
    }

    EXPECT_NEAR(filter.angle(), 4.9f, 0.05f);
}