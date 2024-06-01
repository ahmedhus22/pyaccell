#include <glad/glad.h>
#include <pyaccell/shader.hpp>
#include <pyaccell/rules.hpp>
#include <vector>
#include <cstdlib>
#include <time.h>
#define MAX_STATES 14

int pyaccell::binomial_coefficient(const int n, const int k) {
    if (k==0) return 1;
    std::vector<int> aSolutions(k);
    aSolutions[0] = n - k + 1;

    for (int i = 1; i < k; ++i) {
        aSolutions[i] = aSolutions[i - 1] * (n - k + 1 + i) / (i + 1);
    }

    return aSolutions[k - 1];
}

unsigned int pyaccell::no_of_indices(unsigned int states) {
    unsigned int target = 8;
    return pyaccell::binomial_coefficient(states + target - 1, target);
}

// returns index for given neighbours and max states, N: array of neighbour count for each state
unsigned int pyaccell::get_index(std::vector<int>& N, unsigned int states) {
    int index = 0;
    int y = 8;
    for (int i = 1; i < MAX_STATES; i++) {
        int v = N[i];
        if (v > 0) {
            int x = states - i;
            index += pyaccell::binomial_coefficient(y + x, x) - pyaccell::binomial_coefficient(y - v + x, x);
        }
        y -= v;
    }
    return index;
}

// returns a texture which stores pre-computed binomial coefficients in RED component
unsigned int pyaccell::generate_binomials() {
    unsigned int* data = new unsigned int[32*32]();
    for (int n=1; n<32; n++) {
        for (int k=0; k<32; k++) {
            data[k * 32 + n] = pyaccell::binomial_coefficient(n, k);
        }
    }
    unsigned int binomial_tex; 
    glGenTextures(1, &binomial_tex);
    glBindTexture(GL_TEXTURE_2D, binomial_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32UI, 32, 32, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    delete[] data;

    return binomial_tex;
}

// returns texture which stores rule: delta[index][state] = newstate
unsigned int pyaccell::generate_rule(const unsigned int* rule, size_t indices, size_t states) {
    unsigned int textureRule;
    glGenTextures(1, &textureRule);
    glBindTexture(GL_TEXTURE_2D, textureRule);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8UI, indices, states, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, rule);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    return textureRule;
}

// returns texture which stores input states (initialized to random values) stores input in red channel
unsigned int pyaccell::random_input_state(const unsigned int width, const unsigned int height, const unsigned int states) {
    unsigned int textureInputStates;
    glGenTextures(1, &textureInputStates);
    glBindTexture(GL_TEXTURE_2D, textureInputStates);
    unsigned int* data = new unsigned int[width * height];
    srand(time(0));
    for (int i=0; i<width*height; i++) {
        data[i] = (unsigned int)(rand() % states);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8UI, width, height, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    delete[] data;

    return textureInputStates;
}

// returns empty R32UI texture to store data in red channel
unsigned int pyaccell::create_empty_texture(const unsigned int width, const unsigned int height) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8UI, width, height, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    return texture;
}

unsigned int pyaccell::create_color_texture(const unsigned int width, const unsigned int height) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    return texture;
}