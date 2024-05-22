#version 330 core
layout (location = 0) out uint nextstate;

in vec2 TexCoords;

uniform usampler2D uBinomial;
uniform usampler2D inputStates;
uniform usampler2D rule;
uniform int numStates;
uniform int inputWidth; // width used to create input texture
uniform int inputHeight;
uniform int subIndices;

void main() 
{
    uint curstate = texture(inputStates, TexCoords).r;

    int count = -int(curstate);
    for (int x = -1; x <= 1; x += 1) {
        for (int y = -1; y <= 1; y += 1) {
            int v = int(texture(inputStates, TexCoords + vec2(x / inputWidth, y / inputHeight)).r);
            if (v == 1) {
                count += 1;
            }
        }
    }
    uint newstate = texelFetch(rule, ivec2(count, curstate), 0).r;
    
    nextstate = newstate;
}