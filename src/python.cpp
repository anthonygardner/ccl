#include <pybind11/pybind11.h>

#include <ccl/ccl.hpp>
#include <ccl/pid.hpp>

namespace py = pybind11;

PYBIND11_MODULE(_ccl, m) {
    m.doc() = "Python bindings for the Common Control Library (CCL)";

    m.attr("__all__") = py::make_tuple(
        "hello",
        "PID"
    );

    m.def(
        "hello",
        &ccl::hello,
        "Say hello"
    );

    py::class_<ccl::PID>(m, "PID")
        .def(py::init<>())
        .def(py::init<double, double, double>(), py::arg("kp"), py::arg("ki"), py::arg("kd"))
        .def_readwrite("kp", &ccl::PID::kp)
        .def_readwrite("ki", &ccl::PID::ki)
        .def_readwrite("kd", &ccl::PID::kd)
        .def_readwrite("min_output", &ccl::PID::min_output)
        .def_readwrite("max_output", &ccl::PID::max_output)
        .def("update", &ccl::PID::update, py::arg("setpoint"), py::arg("measurement"), py::arg("dt"))
        .def("reset", &ccl::PID::reset);
}