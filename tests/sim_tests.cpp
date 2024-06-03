#include <gtest/gtest.h>
#include <pyaccell/shader.hpp>
#include <pyaccell/rules.hpp>
#include <pyaccell/automata.hpp>
#include <vector>
#include <array>

/*
    if cmake says no tests found!! rebuild tests and rerun tests
*/

TEST(Rules, BinomialCoeffients) {
    EXPECT_EQ(9, pyaccell::binomial_coefficient(9, 8));
    EXPECT_EQ(1, pyaccell::binomial_coefficient(8, 8));
    EXPECT_EQ(56, pyaccell::binomial_coefficient(8, 3));
}

TEST(Rules, GetIndex) {
    std::array<int, 14> N = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned int states = 3;
    N[3] = 8;
    EXPECT_EQ(0, pyaccell::get_index(N, 3));
    N[1] = 1; N[2] = 6; N[3] = 1;
    EXPECT_EQ(15, pyaccell::get_index(N, 3));
}

TEST(Automata, RunSimulation) {
    std::vector<unsigned int> rule = {
        0,0,0,1,0,0,0,0,0,
        0,0,1,1,0,0,0,0,0
    };
    unsigned int states = 2;
    pyaccell::Automata ca(rule, states);
    EXPECT_FALSE(ca.run());
}

TEST(Automata, RunSimulationsInput) {
    std::vector<unsigned int> rule = {
        0,0,0,1,0,0,0,0,0,
        0,0,1,1,0,0,0,0,0
    };
    unsigned int states = 2;
    pyaccell::Automata ca(rule, states);
    std::vector<unsigned int> input;
    for (int i=0; i<ca.sim_height * ca.sim_width; i++) {
       input.push_back((unsigned int)(1));
    }
    ca.input = input;
    EXPECT_FALSE(ca.run(1));
    for (int i=0; i<10; i++)
        EXPECT_EQ(1, ca.output[i]);
}

/*
#include <pyaccell/engine.hpp>
Tests for function implementation (no longer used)
// runs the simulation to verify output
TEST(Simulations, RunSimulation) {
    std::vector<unsigned int> rule = {
        0,0,0,1,0,0,0,0,0,
        0,0,1,1,0,0,0,0,0
    };
    unsigned int states = 2;
    EXPECT_FALSE(pyaccell::run(&rule[0], states));
}
*/
