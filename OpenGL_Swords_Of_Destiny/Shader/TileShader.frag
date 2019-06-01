#version 330 core

// INPUTS
in vec3 surfaceNormal;
in vec2 out_textureCoordinates;

// OUTPUTS
out vec4 out_Color;

uniform sampler2D textureSampler;
uniform float selected;

vec4 selectedColor = vec4(1.0f, 0.0f, 0.0f, 0.5f);

// FUNCTIONS
void main()
{
	if(selected > 0.5f)
		out_Color = texture(textureSampler, out_textureCoordinates) * selectedColor;
	else
		out_Color = texture(textureSampler, out_textureCoordinates);
}