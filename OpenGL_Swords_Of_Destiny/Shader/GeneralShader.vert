#version 330 core

// INPUTS
in vec3 in_vertexPositions;
in vec2 in_textureCoordinates;
in vec3 in_normalVectors;

// OUTPUTS
out vec3 surfaceNormal;
out vec2 pass_textureCoords;

// UNIFORMS
uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{

	vec4 worldPosition = transformationMatrix * vec4(in_vertexPositions, 1.0f);

	gl_Position = projectionMatrix * viewMatrix * worldPosition;
	
	pass_textureCoords = in_textureCoordinates;
}