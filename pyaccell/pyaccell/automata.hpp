#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace pyaccell {
    class Automata {
        public:
            unsigned int *rule;
            unsigned int states;
            unsigned int sim_width;
            unsigned int sim_height;
            Automata(unsigned int *rule, unsigned int states);
            Automata(unsigned int *rule, unsigned int states, unsigned int sim_width, unsigned int sim_height);
            int run(const unsigned int iterations);
            
        private:
            void processInput(GLFWwindow *window);
    };
}