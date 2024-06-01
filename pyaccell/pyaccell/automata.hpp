#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

namespace pyaccell {
    class Automata {
        public:
            std::vector<unsigned int> rule;
            unsigned int states;
            unsigned int sim_width;
            unsigned int sim_height;
            Automata(std::vector<unsigned int>&rule, unsigned int states);
            Automata(std::vector<unsigned int>&rule, unsigned int states, unsigned int sim_width, unsigned int sim_height);
            int run();
            int run(int iterations);
        private:
            void processInput(GLFWwindow *window);
            enum RUN_TYPE {NO_FINAL_STATE, FINAL_STATE};
    };
}