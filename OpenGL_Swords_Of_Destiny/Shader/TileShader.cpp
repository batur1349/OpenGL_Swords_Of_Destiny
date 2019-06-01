#include "../../pch.h"
#include "TileShader.hpp"


TileShader::TileShader()
	: ShaderProgram("Shader/TileShader")
{
	BindAttributes();
	GetAllUniformLocations();
}

void TileShader::LoadTransformationMatrix(const glm::mat4& matrix)
{
	LoadMatrix4F(m_transformationMatrix_Location, matrix);
}

void TileShader::LoadProjectionMatrix(const glm::mat4& matrix)
{
	LoadMatrix4F(m_projectionMatrix_Location, matrix);
}

void TileShader::LoadViewMatrix(ThirdPersonCamera& camera)
{
	LoadMatrix4F(m_viewMatrix_Location, camera.GetViewMatrix());
}

void TileShader::BindAttributes()
{
	BindAttribute(0, "in_vertexPositions");
	BindAttribute(1, "in_textureCoordinates");
	BindAttribute(2, "in_normalVectors");
}

void TileShader::GetAllUniformLocations()
{
	m_transformationMatrix_Location = GetUniformLocation("transformationMatrix");
	m_projectionMatrix_Location = GetUniformLocation("projectionMatrix");
	m_viewMatrix_Location = GetUniformLocation("viewMatrix");
}
