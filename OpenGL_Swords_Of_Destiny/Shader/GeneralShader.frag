#version 330 core

// INPUTS
in vec3 surfaceNormal;
in vec3 toLightVector[8];
in vec3 toCameraVector;
in vec2 pass_textureCoords;
in float visibility;

// OUTPUTS
out vec4 outColor;

// UNIFORM
uniform sampler2D textureSampler;
uniform vec3 lightColor[8];
uniform float selected;
uniform float shineDamper;
uniform float reflectivity;
uniform float useFog;

// CONSTS
const float m_ambientStrength = 0.1f;
vec4 selectedColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
vec3 skyColor = vec3(0.5444f, 0.62f, 0.69f);

void main()
{
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitVectorToCamera = normalize(toCameraVector);

	vec3 totalDiffuse = vec3(0.0f);
	vec3 totalSpecular = vec3(0.0f);

	for(int i = 0; i < 8; i++)
	{
		vec3 unitLightVector = normalize(toLightVector[i]);
		float nDotl = dot(unitNormal, unitLightVector);
		float brightness = max(nDotl, 0.0f);
		vec3 lightDirection = -unitLightVector;
		vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
		float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
		specularFactor = max(specularFactor, 0.0f);
		float dampedFactor = pow(specularFactor, shineDamper);
		totalDiffuse = totalDiffuse + brightness * lightColor[i];
		totalSpecular = totalSpecular + dampedFactor * reflectivity * lightColor[i];
	}
	totalDiffuse = max(totalDiffuse, 0.2f);

	vec4 textureColor = texture(textureSampler, pass_textureCoords);
	if(textureColor.a < 0.5f)
	{
		discard;
	}

	if(selected > 0.5f)
	{
		outColor = selectedColor * vec4(totalDiffuse, 1.0f) + vec4(totalSpecular, 1.0f);
		outColor = mix(outColor, textureColor, 0.15f);
	}
	else
	{
		outColor = vec4(totalDiffuse, 1.0f) * textureColor + vec4(totalSpecular, 1.0f);
		if(useFog > 0.5f)
		{
			outColor = mix(vec4(skyColor, 1.0f), outColor, visibility);
		}
	}
}