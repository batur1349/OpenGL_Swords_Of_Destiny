#include "../pch.h"
#include "GuiShader.hpp"


GuiShader::GuiShader()
	: ShaderProgram("Gui/guiShader")
{
	BindAttributes();
	GetAllUniformLocation();
}

void GuiShader::LoadTransformationMatrix(glm::mat4 matrix)
{
	LoadMatrix4F(_location_transformationMatrix, matrix);
}

void GuiShader::BindAttributes()
{
	BindAttribute(0, "position");
}

void GuiShader::GetAllUniformLocation()
{
	_location_transformationMatrix = GetUniformLocation("transformationMatrix");
}
