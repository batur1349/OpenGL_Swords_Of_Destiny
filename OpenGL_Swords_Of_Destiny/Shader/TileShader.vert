#version 330 core

// INPUTS
in vec3 in_vertexPositions;
in vec2 in_textureCoordinates;
in vec3 in_normalVectors;

// OUTPUTS
out vec2 out_textureCoordinates;
out vec3 surfaceNormal;

// UNIFORMS
uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

// FUNCTIONS
void main()
{
	vec4 worldPosition = transformationMatrix * vec4(in_vertexPositions, 1.0f);
	
	gl_Position = projectionMatrix * viewMatrix * worldPosition;

	out_textureCoordinates = in_textureCoordinates * 32;

	surfaceNormal = (transformationMatrix * vec4(in_normalVectors, 0.0f)).xyz;	
}