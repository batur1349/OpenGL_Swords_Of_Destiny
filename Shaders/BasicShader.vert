#version 330 core

// INPUTS
in vec3 in_vertexPositions;

// OUTPUTS
out vec3 colour;

// FUNCTIONS
void main()
{
	gl_Position = vec4(in_vertexPositions, 1.0f);
	colour = vec3(in_vertexPositions.x + 0.5f, 1.0f, in_vertexPositions.y + 0.5f);
}