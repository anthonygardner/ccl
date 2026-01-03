#pragma once

namespace ccl {

class ComplementaryFilter {
public:
    ComplementaryFilter(float gyro_weight, float dt);

    float update(float accel_angle, float gyro_rate);
    
    // Getters
    float angle() const { return angle_; }
    float gyro_weight() const { return gyro_weight_; }
    float dt() const { return dt_; }

    float time_constant() const {
        return dt_ * gyro_weight_ / (1.0f - gyro_weight_);
    }

private:
    float angle_ = 0.0;
    bool initialized_ = false;

    const float gyro_weight_;
    const float dt_;
};

} // namespace ccl