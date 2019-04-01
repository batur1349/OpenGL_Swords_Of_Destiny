#version 330 core

// INPUTS
in vec3 colour;

// OUTPUTS
out vec4 out_Color;

// FUNCTIONS
void main()
{
	out_Color = vec4(colour, 1.0f);
}