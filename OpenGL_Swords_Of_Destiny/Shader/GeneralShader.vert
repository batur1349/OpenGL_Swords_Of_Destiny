#version 330 core

// INPUTS
in vec3 in_vertexPositions;
in vec2 in_textureCoordinates;
in vec3 in_normalVectors;

// OUTPUTS
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec2 pass_textureCoords;

// UNIFORMS
uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform vec3 lightPosition;

void main()
{

	vec4 worldPosition = transformationMatrix * vec4(in_vertexPositions, 1.0f);

	gl_Position = projectionMatrix * viewMatrix * worldPosition;
	
	pass_textureCoords = in_textureCoordinates;

	surfaceNormal = (transformationMatrix * vec4(in_normalVectors, 0.0f)).xyz;
	toLightVector = lightPosition - worldPosition.xyz;
}