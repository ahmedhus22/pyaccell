#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform usampler2D states;

void main()
{
    uint state = texture(states, TexCoords).r;
    vec3 col = vec3(float(state));
    
    FragColor = vec4(col, 1.0);
} 