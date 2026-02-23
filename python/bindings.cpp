#include <pybind11/pybind11.h>

#include "ccl/ccl.hpp"
#include "ccl/pid.hpp"

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
        .def_property("kp", &ccl::PID::get_kp, &ccl::PID::set_kp)
        .def_property("ki", &ccl::PID::get_ki, &ccl::PID::set_ki)
        .def_property("kd", &ccl::PID::get_kd, &ccl::PID::set_kd)
        .def_property("min_output", &ccl::PID::get_min_output, &ccl::PID::set_min_output)
        .def_property("max_output", &ccl::PID::get_max_output, &ccl::PID::set_max_output)
        .def("update", &ccl::PID::update, py::arg("setpoint"), py::arg("measurement"), py::arg("dt"))
        .def("reset", &ccl::PID::reset);
}