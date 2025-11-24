// bindings/pybind11/sparkcan_bindings.cpp
#include <pybind11/pybind11.h>
#include <string>
#include <cstdint>

#include "SparkBase.hpp"
#include "SparkFlex.hpp"
#include "SparkMax.hpp"

namespace py = pybind11;
using guard = py::call_guard<py::gil_scoped_release>;

PYBIND11_MODULE(_sparkcan, m) {
    m.doc() = "Minimal Python bindings for SparkCAN: SetPosition, SetVelocity, GetAbsoluteEncoderPosition, GetVelocity, Heartbeat";

    // Bind just the requested SparkBase APIs so SparkFlex/Max inherit them.
    py::class_<SparkBase>(m, "SparkBase")
        .def("SetPosition", &SparkBase::SetPosition, py::arg("position"), guard())
        .def("SetVelocity", &SparkBase::SetVelocity, py::arg("velocity"), guard())
        .def("GetAbsoluteEncoderPosition", &SparkBase::GetAbsoluteEncoderPosition, guard())
        .def("GetVelocity", &SparkBase::GetVelocity, guard())
        .def("Heartbeat", &SparkBase::Heartbeat, guard())
        .def("heartbeat", &SparkBase::Heartbeat, guard());  // alias

    // Concrete devices (inherit SparkBase methods)
    py::class_<SparkFlex, SparkBase>(m, "SparkFlex")
        .def(py::init<const std::string&, uint8_t>(),
             py::arg("interface"), py::arg("device_id"));

    py::class_<SparkMax, SparkBase>(m, "SparkMax")
        .def(py::init<const std::string&, uint8_t>(),
             py::arg("interface"), py::arg("device_id"));
}
