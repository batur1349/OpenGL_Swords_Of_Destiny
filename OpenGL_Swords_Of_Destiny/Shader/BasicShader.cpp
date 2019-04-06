#include "../pch.h"
#include "BasicShader.hpp"


BasicShader::BasicShader()
	: Shader("../Shaders/BasicShader")
{
	BindAttributes();
	GetAllUniformLocations();
}

BasicShader::BasicShader(const std::string & fileName)
	: Shader(fileName)
{
	BindAttributes();
	GetAllUniformLocations();
}

void BasicShader::LoadTransformationMatrix(glm::mat4 matrix)
{
	LoadMatrix4f(_location_transformationMatrix, matrix);
}

void BasicShader::LoadProjectionMatrix(glm::mat4 matrix)
{
	LoadMatrix4f(_location_projectionMatrix, matrix);
}

void BasicShader::LoadViewMatrix(Camera camera)
{
	glm::mat4 viewMatrix = Maths::CreateViewMatrix(camera);

	LoadMatrix4f(_location_viewMatrix, viewMatrix, false);
}

void BasicShader::LoadLightVariables(Light light)
{
	LoadVector3F(_location_lightPosition, light.GetPosition());
	LoadVector3F(_location_lightColor, light.GetColor());
}

void BasicShader::BindAttributes()
{
	BindAttribute(0, "in_vertexPositions");
	BindAttribute(1, "in_textureCoordinates");
	BindAttribute(2, "in_normalVectors");
}

void BasicShader::GetAllUniformLocations()
{
	_location_transformationMatrix = GetUniformLocation("transformationMatrix");
	_location_projectionMatrix = GetUniformLocation("projectionMatrix");
	_location_viewMatrix = GetUniformLocation("viewMatrix");
	_location_lightPosition = GetUniformLocation("lightPosition");
	_location_lightColor = GetUniformLocation("lightColor");
}
