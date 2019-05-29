#version 330 core

// INPUTS
in vec3 surfaceNormal;
in vec2 pass_textureCoords;

// OUTPUTS
out vec4 outColor;

// UNIFORM
uniform sampler2D textureSampler;

void main()
{
    outColor = texture(textureSampler, pass_textureCoords);
}