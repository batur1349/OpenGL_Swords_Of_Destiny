#version 330 core

// INPUTS
in vec3 surfaceNormal;
in vec2 out_textureCoordinates;
in float visibility;

// OUTPUTS
out vec4 out_Color;

uniform sampler2D textureSampler;
uniform sampler2D selectedSampler;
uniform sampler2D bloodSampler;
uniform float selected;
uniform float useFog;

vec3 skyColor = vec3(0.5444f, 0.62f, 0.69f);

// FUNCTIONS
void main()
{
	if(selected > 0.5f)
	{
		vec4 tileTexture = texture(textureSampler, out_textureCoordinates);
		vec4 selectedTexture = texture(selectedSampler, out_textureCoordinates);

		out_Color = mix(tileTexture, selectedTexture, 0.5f);
		if(useFog > 0.5f)
		{
			out_Color = mix(vec4(skyColor, 1.0f), out_Color, visibility);
		}
	}
	else
	{
		out_Color = texture(textureSampler, out_textureCoordinates);
		if(useFog > 0.5f)
		{
			out_Color = mix(vec4(skyColor, 1.0f), out_Color, visibility);
		}
	}
}