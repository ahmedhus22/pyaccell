#include <nanobind/nanobind.h>
#include <nanobind/stl/bind_vector.h>
#include <nanobind/stl/array.h>
#include <pyaccell/automata.hpp>
#include <pyaccell/rules.hpp>
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
        .def(nb::init<UIntVector &, unsigned int>(), "rule"_a, "states"_a)
        .def(nb::init<UIntVector &, unsigned int, unsigned int, unsigned int>(), "rule"_a, "states"_a, "sim_width"_a, "sim_height"_a)
        .def("run", nb::overload_cast<>(&pyaccell::Automata::run), "run simulation indefinitely")
        .def("run", nb::overload_cast<int>(&pyaccell::Automata::run), "iterations"_a, "run simulation for set iterations, then stop")
        .def_rw("states", &pyaccell::Automata::states)
        .def_rw("input", &pyaccell::Automata::input)
        .def_ro("output", &pyaccell::Automata::output)
        .def_rw("sim_width", &pyaccell::Automata::sim_width)
        .def_rw("sim_height", &pyaccell::Automata::sim_height);
    m.def("vec_to_list", &vec_to_list<unsigned int>, "vector"_a, "returns a list for given vector(to convert output)");
    m.def("max_index", &pyaccell::no_of_indices, "returns max no of indices for given no. of states");
    m.def("get_index", &pyaccell::get_index, "returns the index for given neighbours(list of size 14) and max states");
    m.doc() = "A GPU Accelerated Cellular Automata Library";
}