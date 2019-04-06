#version 330 core

// INPUTS
in vec3 in_vertexPositions;
in vec2 in_textureCoordinates;

// OUTPUTS
out vec2 out_textureCoordinates;

// UNIFORMS
uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

// FUNCTIONS
void main()
{
	gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(in_vertexPositions, 1.0f);
	out_textureCoordinates = in_textureCoordinates;
}