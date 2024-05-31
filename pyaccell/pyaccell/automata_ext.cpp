#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <pyaccell/automata.hpp>
#include <vector>

namespace nb = nanobind;
using namespace nb::literals;
using UIntVector = std::vector<unsigned int>;

NB_MODULE(pyaccell_ext, m) {
    nb::class_<pyaccell::Automata>(m, "Automata")
        .def(nb::init<UIntVector &, unsigned int>())
        .def(nb::init<UIntVector &, unsigned int, unsigned int, unsigned int>())
        .def("run", &pyaccell::Automata::run)
        .def_rw("states", &pyaccell::Automata::states)
        .def_rw("sim_width", &pyaccell::Automata::sim_width)
        .def_rw("sim_height", &pyaccell::Automata::sim_height);
    m.doc() = "A GPU Accelerated Cellular Automata Library";
}