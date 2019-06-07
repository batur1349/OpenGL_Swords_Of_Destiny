#version 330 core

// INPUTS
in vec3 surfaceNormal;
in vec2 out_textureCoordinates;

// OUTPUTS
out vec4 out_Color;

uniform sampler2D textureSampler;
uniform sampler2D selectedSampler;
uniform float selected;

// FUNCTIONS
void main()
{
	if(selected > 0.5f)
	{
		out_Color = mix(texture(textureSampler, out_textureCoordinates), texture(selectedSampler, out_textureCoordinates), 0.5f);
	}
	else
	{
		out_Color = texture(textureSampler, out_textureCoordinates);
	}
}