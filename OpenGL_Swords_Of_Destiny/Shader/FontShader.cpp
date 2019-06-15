#include "../pch.h"
#include "FontShader.hpp"


FontShader::FontShader()
	: ShaderProgram("Shader/fontShader")
{
	BindAttributes();
	GetAllUniformLocations();
}

void FontShader::LoadTextColor(const glm::vec3& color)
{
	LoadVector3F(m_textColor_Location, color);
}

void FontShader::LoadProjectionMatrix(const glm::mat4& matrix)
{
	LoadMatrix4F(m_projection_Location, matrix);
}

void FontShader::BindAttributes()
{
	//BindAttribute(0, "vertex");
}

void FontShader::GetAllUniformLocations()
{
	m_textColor_Location = GetUniformLocation("textColor");
	m_projection_Location = GetUniformLocation("projection");
}
