#include <glad/glad.h>
#include <pyaccell/shader.hpp>
#include <pyaccell/rules.hpp>
#include <vector>
#include <cstdlib>

int pyaccell::binomial_coefficient(const int n, const int k) {
    if (k==0) return 1;
    std::vector<int> aSolutions(k);
    aSolutions[0] = n - k + 1;

    for (int i = 1; i < k; ++i) {
        aSolutions[i] = aSolutions[i - 1] * (n - k + 1 + i) / (i + 1);
    }

    return aSolutions[k - 1];
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32UI, 32, 32, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, data);
    delete[] data;

    return binomial_tex;
}

// returns texture which stores rule: delta[state][index] = newstate
// Test this
unsigned int pyaccell::generate_rule(unsigned int *rule, size_t states, size_t indices) {
    unsigned int textureRule;
    glGenTextures(1, &textureRule);
    glBindTexture(GL_TEXTURE_2D, textureRule);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32UI, states, indices, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, rule);
    return textureRule;
}

// returns texture which stores input states (initially random)
unsigned int pyaccell::random_input_state(const unsigned int width, const unsigned int height, const unsigned int states) {
    unsigned int textureInputStates;
    glGenTextures(1, &textureInputStates);
    glBindTexture(GL_TEXTURE_2D, textureInputStates);
    unsigned int* data = new unsigned int[width * height];
    for (int i=0; i<width*height; i++) {
        data[i] = (unsigned int)(rand() % states);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    delete[] data;

    return textureInputStates;
}
