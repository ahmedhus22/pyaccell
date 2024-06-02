#version 330 core
layout (location = 0) out vec3 col;
layout (location = 1) out uint nextstate;

in vec2 TexCoords;

uniform usampler2D uBinomial;
uniform usampler2D inputStates;
uniform usampler2D rule;
uniform sampler2D colorMap;
uniform int numStates;
uniform int inputWidth; // width used to create input texture
uniform int inputHeight;

const float offset = 1.0 / 3000.0;

// returns binomial coefficient (n choose k) from precompute texture
int binomial(int n, int k) {
    return int(texelFetch(uBinomial, ivec2(n, k), 0).r);
}

void main() 
{
    uint curstate = texture(inputStates, TexCoords).r;

    int N[14] = int[](0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    N[curstate] = -1;
    for (int x = -1; x <= 1; x += 1) {
        for (int y = -1; y <= 1; y += 1) {
            int v = int(texture(inputStates, TexCoords + vec2((x + offset)/ inputWidth, (y + offset)/ inputHeight)).r);
            N[v] += 1; 
        }
    }

    int index = 0;
    int y = 8;
    for (int i = 1; i < 14; i++) {
        int v = N[i];
        if (v > 0) {
            int x = numStates - i;
            index += binomial(y + x, x) - binomial(y - v + x, x);
        }
        y -= v;
    }

    uint newstate = texelFetch(rule, ivec2(index, curstate), 0).r;
    
    nextstate = newstate;
    col = texture(colorMap, vec2((float(nextstate) + 0.5) / 14.0, 0.5)).rgb;
}