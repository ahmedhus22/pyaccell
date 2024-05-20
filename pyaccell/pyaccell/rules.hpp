#pragma once

namespace pyaccell {
    int binomial_coefficient(const int n, const int k);
    unsigned int generate_binomials();
    unsigned int generate_rule(unsigned int *rule, size_t states, size_t indices);
    unsigned int random_input_state(const unsigned int width, const unsigned int height);
}