#version 330 core

// INPUTS
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec2 pass_textureCoords;

// OUTPUTS
out vec4 outColor;

// UNIFORM
uniform sampler2D textureSampler;
uniform vec3 lightColor;
uniform float selected;

// CONSTS
const float m_ambientStrength = 0.1f;
vec4 selectedColor = vec4(0.875f, 0.875f, 0.875f, 1.0f);

void main()
{
	// Ambient Color Calculation
	vec3 ambient = m_ambientStrength * lightColor;

	// Diffuse Color Calculation
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);
	float brightness = max(dot(unitNormal, unitLightVector), 0.05f);
	vec3 diffuse = brightness * lightColor;

	if(selected > 0.5f)
	{
		outColor = vec4(selectedColor * (texture(textureSampler, pass_textureCoords)));
	}
	else
	{
		outColor = vec4((ambient + diffuse)* (texture(textureSampler, pass_textureCoords)), 1.0f);
	}
}