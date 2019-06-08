#version 330 core

// INPUTS
in vec3 surfaceNormal;
in vec2 out_textureCoordinates;

// OUTPUTS
out vec4 out_Color;

uniform sampler2D textureSampler;
uniform sampler2D selectedSampler;
uniform sampler2D bloodSampler;
uniform float selected;

// FUNCTIONS
void main()
{
	if(selected > 0.5f)
	{
		vec4 tileTexture = texture(textureSampler, out_textureCoordinates);
		vec4 selectedTexture = texture(selectedSampler, out_textureCoordinates);

		if(selectedTexture.rgb == vec3(0.0f, 0.0f, 0.0f))
		{
			tileTexture.rgb = vec3(0.0f, 0.0f, 0.0f);	
		}

		out_Color = mix(tileTexture, selectedTexture, 0.3f);
	}
	//else if(blood > 0.5f)
	//{
	//	vec4 tileTexture = texture(textureSampler, out_textureCoordinates);
	//	vec4 bloodTexture = texture(bloodSampler, out_textureCoordinates);
	//
	//	if(bloodTexture.a < 0.5f)
	//	{
	//		bloodTexture.rgb = tileTexture.rgb;
	//	}
	//
	//	out_Color = mix(tileTexture, bloodTexture, 1.0f);
	//}
	else
	{
		out_Color = texture(textureSampler, out_textureCoordinates);
	}
}