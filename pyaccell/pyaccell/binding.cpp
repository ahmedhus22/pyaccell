#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <pyaccell/engine.hpp>
#include <vector>

namespace nb = nanobind;
using namespace nb::literals;
using UIntVector = std::vector<unsigned int>;

int run_ca(const UIntVector &rule, const unsigned int states) { 
    return pyaccell::run(&rule[0], states);
}

NB_MODULE(pyaccell_ext, m) {
    m.def("run_ca", &run_ca, "rule"_a, "states"_a, 
        "runs cellular automata simulation with given rule as a list cols=indices, rows=states.");
    m.doc() = "A GPU Accelerated Cellular Automata Library";
}