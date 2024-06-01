#include <nanobind/nanobind.h>
#include <nanobind/stl/bind_vector.h>
#include <pyaccell/automata.hpp>
#include <vector>

namespace nb = nanobind;
using namespace nb::literals;
using UIntVector = std::vector<unsigned int>;

template <typename T>
nb::list vec_to_list(std::vector<T> vec) {
    nb::list l;
    for(auto i: vec) {
        l.append(i);
    }
    return l;
}

NB_MODULE(pyaccell_ext, m) {
    nb::bind_vector<UIntVector>(m, "UIntVector");
    nb::class_<pyaccell::Automata>(m, "Automata")
        .def(nb::init<UIntVector &, unsigned int>())
        .def(nb::init<UIntVector &, unsigned int, unsigned int, unsigned int>())
        .def("run", nb::overload_cast<>(&pyaccell::Automata::run), "run simulation indefinitely")
        .def("run", nb::overload_cast<int>(&pyaccell::Automata::run), "run simulation for set iterations, then stop")
        .def_rw("states", &pyaccell::Automata::states)
        .def_ro("output", &pyaccell::Automata::output)
        .def_rw("sim_width", &pyaccell::Automata::sim_width)
        .def_rw("sim_height", &pyaccell::Automata::sim_height);
    m.def("vec_to_list", &vec_to_list<unsigned int>);
    m.doc() = "A GPU Accelerated Cellular Automata Library";
}