#include "../pch.h"
#include "BasicShader.hpp"


BasicShader::BasicShader()
	: Shader("../Shaders/BasicShader")
{
	BindAttributes();
}

BasicShader::BasicShader(const std::string & fileName)
	: Shader(fileName)
{
	BindAttributes();
}

void BasicShader::BindAttributes()
{
	BindAttribute(0, "in_vertexPositions");
	BindAttribute(1, "in_textureCoordinates");
}
