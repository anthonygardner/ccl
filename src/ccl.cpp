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

    tcsetattr(fd, TCSANOW, &tty);

    ComplementaryFilter pitch_filter(0.98f, 0.1f);
    ComplementaryFilter roll_filter(0.98f, 0.1f);

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

            float pitch_rad = std::atan2(-ax, std::sqrt(ay * ay + az * az));
            float roll_rad = std::atan2(ay, std::sqrt(ax * ax + az * az));

            float pitch = pitch_filter.update(pitch_rad, gy * M_PI / 180.0f);
            float roll = roll_filter.update(roll_rad, gx * M_PI / 180.0f);

            std::cout << timestamp << "," << pitch << "," << roll << std::endl;

            line_buffer.clear();
        } else {
            line_buffer += c;
        }
    }

    close(fd);
    return 0;
}

} // namespace ccl