#version 330 core

// INPUTS
in vec3 surfaceNormal;

// OUTPUTS
out vec4 outColor;


void main()
{
    outColor = vec4(surfaceNormal, 1.0f);
}