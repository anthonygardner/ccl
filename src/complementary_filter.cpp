#include <ccl/complementary_filter.hpp>

namespace ccl {

ComplementaryFilter::ComplementaryFilter(float gyro_weight, float dt) 
    : gyro_weight_(gyro_weight), dt_(dt) {}

float ComplementaryFilter::update(float accel_angle, float gyro_rate) {
    angle_ = gyro_weight_ * (angle_ + gyro_rate * dt_) + (1.0f - gyro_weight_) * accel_angle;
    return angle_;
}

} // namespace ccl