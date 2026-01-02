#include <pybind11/pybind11.h>

#include "mylib.hpp"

namespace py = pybind11;

PYBIND11_MODULE(_mylib, m) {
    m.doc() = "mylib Python bindings";

    m.def(
        "hello",
        &mylib::hello,
        "Say hello"
    );
}