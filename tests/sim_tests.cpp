#include <gtest/gtest.h>
#include <pyaccell/shader.hpp>
#include <pyaccell/rules.hpp>
#include <pyaccell/engine.hpp>

/*
    if cmake says no tests found!! rebuild tests and rerun tests
*/

TEST(Rules, BinomialCoeffients) {
    EXPECT_EQ(9, pyaccell::binomial_coefficient(9, 8));
    EXPECT_EQ(1, pyaccell::binomial_coefficient(8, 8));
    EXPECT_EQ(56, pyaccell::binomial_coefficient(8, 3));
}

// runs the simulation to verify output
TEST(Simulations, RunSimulation) {
    EXPECT_FALSE(pyaccell::run());
}
