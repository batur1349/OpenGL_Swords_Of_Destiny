#version 330 core

// INPUTS
in vec3 in_vertexPositions;
in vec2 in_textureCoordinates;
in vec3 in_normalVectors;

// OUTPUTS
out vec3 surfaceNormal;
out vec3 toLightVector[8];
out vec3 toCameraVector;
out vec2 pass_textureCoords;
out float visibility;

// UNIFORMS
uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform float fakeLightning;

uniform vec3 lightPosition[8];

const float density = 0.007;
const float gradient = 5.0;

void main()
{
	vec4 worldPosition = transformationMatrix * vec4(in_vertexPositions, 1.0f);
	vec4 positionRelativeToCamera = viewMatrix * worldPosition;
	gl_Position = projectionMatrix * positionRelativeToCamera;

	pass_textureCoords = in_textureCoordinates;

	vec3 actualNormal = in_normalVectors;
	if(fakeLightning > 0.5f)
	{
		actualNormal = vec3(0.0f, 1.0f, 0.0f);
	}

	surfaceNormal = (transformationMatrix * vec4(actualNormal, 0.0f)).xyz;

	for(int i = 0; i < 8; i++)
	{
		toLightVector[i] = lightPosition[i] - worldPosition.xyz;
	}

	toCameraVector = (inverse(viewMatrix) * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz - worldPosition.xyz;

	float distance = length(positionRelativeToCamera.xyz);
	visibility = exp(-pow((distance * density), gradient));
	visibility = clamp(visibility, 0.0f, 1.0f);
}