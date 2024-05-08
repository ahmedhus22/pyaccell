#include <glad/glad.h>
#include <pyaccell/shader.hpp>
#include <pyaccell/rules.hpp>
#include <vector>

int pyaccell::binomial_coefficient(const int n, const int k) {
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
    for (int n=0; n<32; n++) {
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

