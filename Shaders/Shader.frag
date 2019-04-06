#version 330 core

// INPUTS
in vec2 out_textureCoordinates;
in vec3 surfaceNormal;
in vec3 toLightVector;

// OUTPUTS
out vec4 out_Color;

// UNIFORMS
uniform sampler2D textureSampler;
uniform vec3 lightColor;

// FUNCTIONS
void main()
{
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);

	float nDot1 = dot(unitNormal, unitLightVector);
	float brightness = max(nDot1, 0.1f);
	vec3 diffuse = brightness * lightColor;

	out_Color = vec4(diffuse, 1.0f) * texture(textureSampler, out_textureCoordinates);
}