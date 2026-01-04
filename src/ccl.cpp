#include <cmath>
#include <iostream>
#include <sstream>

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <ccl/ccl.hpp>
#include <ccl/complementary_filter.hpp>

namespace ccl {

std::string hello() {
    return "Hello, world!";
}

int run(const char* device, speed_t baud) {
    int fd = open(device, O_RDONLY | O_NOCTTY);
    if (fd < 0) {
        std::cerr << "Failed to open " << device << std::endl;
        return 1;
    }

    // https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/
    termios tty;
    tcgetattr(fd, &tty);

    cfsetispeed(&tty, B115200);

    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;

    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);

    tty.c_cc[VMIN] = 1;   // Block until at least 1 byte
    tty.c_cc[VTIME] = 0;  // No timeout

    tcsetattr(fd, TCSANOW, &tty);

    ComplementaryFilter pitch_filter(0.9f, 0.1f);
    ComplementaryFilter roll_filter(0.9f, 0.1f);

    std::string line_buffer;
    char c;

    while (read(fd, &c, 1) > 0) {
        if (c == '\n') {
            // Parse: timestamp,ax,ay,az,temp,gx,gy,gz
            std::stringstream ss(line_buffer);
            std::string token;
            float values[8];
            int i = 0;

            while (std::getline(ss, token, ',') && i < 8) {
                values[i++] = std::stof(token);
            }

            float timestamp = values[0];
            float ax = values[1];
            float ay = values[2];
            float az = values[3];
            float temp = values[4];
            float gx = values[5];
            float gy = values[6];
            float gz = values[7];

            constexpr float ax_bias = 0.02f;
            constexpr float ay_bias = 0.02f;
            constexpr float az_bias = 0.02f;

            float ax_corrected = ax - ax_bias;
            float ay_corrected = ay - ay_bias;
            float az_corrected = az - az_bias;

            // Compute tilt angles from accelerometer (radians)
            float accel_pitch = std::atan2(-ax_corrected, std::sqrt(ay_corrected * ay_corrected + az_corrected * az_corrected));
            float accel_roll = std::atan2(ay_corrected, std::sqrt(ax_corrected * ax_corrected + az_corrected * az_corrected));

            // Convert gyro rates from deg/s to rad/s
            float gyro_pitch_rate = gy * M_PI / 180.0f;
            float gyro_roll_rate = gx * M_PI / 180.0f;

            // Fuse measurements
            float fused_pitch = pitch_filter.update(accel_pitch, gyro_pitch_rate);
            float fused_roll = roll_filter.update(accel_roll, gyro_roll_rate);

            // Output in degrees
            float pitch_deg = fused_pitch * 180.0f / M_PI;
            float roll_deg = fused_roll * 180.0f / M_PI;

            std::cout << timestamp << "," << pitch_deg << "," << roll_deg << std::endl;

            line_buffer.clear();
        } else {
            line_buffer += c;
        }
    }

    close(fd);
    return 0;
}

} // namespace ccl