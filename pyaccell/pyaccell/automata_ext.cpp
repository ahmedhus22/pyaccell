#include <nanobind/nanobind.h>
#include <nanobind/stl/bind_vector.h>
#include <pyaccell/automata.hpp>
#include <vector>

namespace nb = nanobind;
using namespace nb::literals;
using UIntVector = std::vector<unsigned int>;

NB_MODULE(pyaccell_ext, m) {
    nb::bind_vector<UIntVector>(m, "UIntVector");
    nb::class_<pyaccell::Automata>(m, "Automata")
        .def(nb::init<UIntVector &, unsigned int>())
        .def(nb::init<UIntVector &, unsigned int, unsigned int, unsigned int>())
        .def("run", nb::overload_cast<>(&pyaccell::Automata::run), "run simulation indefinitely")
        .def("run", nb::overload_cast<int, UIntVector &>(&pyaccell::Automata::run), "run simulation for set iterations, then stop")
        .def_rw("states", &pyaccell::Automata::states)
        .def_rw("sim_width", &pyaccell::Automata::sim_width)
        .def_rw("sim_height", &pyaccell::Automata::sim_height);
    m.doc() = "A GPU Accelerated Cellular Automata Library";
}