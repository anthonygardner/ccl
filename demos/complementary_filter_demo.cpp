#include <ccl/ccl.hpp>

int main(int argc, char* argv[]) {
    const char* device = "/dev/ttyACM0";

    if (argc > 1) {
        device = argv[1];
    }

    return ccl::run(device, 115200);
}