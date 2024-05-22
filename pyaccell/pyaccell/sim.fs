#version 330 core
layout (location = 0) out uint FragColor;

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
    
    FragColor = curstate;
}