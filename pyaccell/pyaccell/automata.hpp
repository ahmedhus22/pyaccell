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
            std::vector<unsigned int> output;
            std::vector<unsigned int> input;
            Automata(std::vector<unsigned int>&rule, unsigned int states);
            Automata(std::vector<unsigned int>&rule, unsigned int states, unsigned int sim_width, unsigned int sim_height);
            int run();
            int run(int iterations);
        private:
            void processInput(GLFWwindow *window);
            std::vector<unsigned int> get_texture_data(unsigned int texture, const unsigned int width, const unsigned int height);
            unsigned int create_color_map();
            unsigned int create_input_texture();
            enum RUN_TYPE {NO_FINAL_STATE, FINAL_STATE};
    };
}