#pragma once
#define MAX_STATES 14
#include <vector>
#include <array>

namespace pyaccell {
    int binomial_coefficient(const int n, const int k);
    unsigned int generate_binomials();
    unsigned int no_of_indices(unsigned int states);
    unsigned int get_index(std::array<int, MAX_STATES>& N, unsigned int states);
    unsigned int generate_rule(const unsigned int* rule, size_t indices, size_t states);
    unsigned int random_input_state(const unsigned int width, const unsigned int height, const unsigned int states);
    unsigned int create_empty_texture(const unsigned int width, const unsigned int height);
    unsigned int create_color_texture(const unsigned int width, const unsigned int height);
}