#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D uBinomial;
uniform sampler2D inputStates;
uniform sampler2D rule;
uniform int numStates;
uniform int inputWidth; // width used to create input texture
uniform int subIndices;

int binomial(int n, int k) {
    return int(texelFetch(uBinomial, ivec2(n, k), 0).r);
}

void main() 
{
    int curstate = int(texture(inputStates, TexCoords).r);
    
    vec3 color = vec3(curstate);
    FragColor = vec4(color, 1.0);
}