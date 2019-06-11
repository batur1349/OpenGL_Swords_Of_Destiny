#version 330 core

// INPUTS
in vec3 in_vertexPositions;
in vec2 in_textureCoordinates;
in vec3 in_normalVectors;

// OUTPUTS
out vec2 out_textureCoordinates;
out vec3 surfaceNormal;
out float visibility;

// UNIFORMS
uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

const float density = 0.007;
const float gradient = 5.0;

// FUNCTIONS
void main()
{
	vec4 worldPosition = transformationMatrix * vec4(in_vertexPositions, 1.0f);
	vec4 positionRelativeToCamera = viewMatrix * worldPosition;
	gl_Position = projectionMatrix * positionRelativeToCamera;
	out_textureCoordinates = in_textureCoordinates;
	surfaceNormal = (transformationMatrix * vec4(in_normalVectors, 0.0f)).xyz;	

	float distance = length(positionRelativeToCamera.xyz);
	visibility = exp(-pow((distance * density), gradient));
	visibility = clamp(visibility, 0.0f, 1.0f);
}