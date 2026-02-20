#pragma once

#include <string>

#include <termios.h>

namespace ccl {

std::string hello();

int run(const char* device, speed_t baud);

} // namespace ccl