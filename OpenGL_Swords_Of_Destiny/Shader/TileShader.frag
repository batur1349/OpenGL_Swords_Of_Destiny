#version 330 core

// INPUTS
in vec3 surfaceNormal;
in vec2 out_textureCoordinates;

// OUTPUTS
out vec4 out_Color;

uniform sampler2D textureSampler;

// FUNCTIONS
void main()
{
	out_Color = texture(textureSampler, out_textureCoordinates);
}