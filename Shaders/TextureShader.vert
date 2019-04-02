#version 330 core

// INPUTS
in vec3 in_vertexPositions;
in vec2 in_textureCoordinates;

// OUTPUTS
out vec2 out_textureCoordinates;

// FUNCTIONS
void main()
{
	gl_Position = vec4(in_vertexPositions, 1.0f);
	out_textureCoordinates = in_textureCoordinates;
}