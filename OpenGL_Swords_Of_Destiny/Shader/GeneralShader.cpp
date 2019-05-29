#include "../pch.h"
#include "GeneralShader.hpp"


GeneralShader::GeneralShader()
	: ShaderProgram("Shader/GeneralShader")
{
	BindAttributes();
	GetAllUniformLocations();
}

void GeneralShader::LoadTransformationMatrix(const glm::mat4& matrix)
{
	LoadMatrix4F(m_transformationMatrix_Location, matrix);
}

void GeneralShader::LoadProjectionMatrix(const glm::mat4& matrix)
{
	LoadMatrix4F(m_projectionMatrix_Location, matrix);
}

void GeneralShader::LoadViewMatrix(ThirdPersonCamera& camera)
{
	LoadMatrix4F(m_viewMatrix_Location, camera.GetViewMatrix());
}

void GeneralShader::BindAttributes()
{
	BindAttribute(0, "in_vertexPositions");
	BindAttribute(1, "in_textureCoordinates");
	BindAttribute(2, "in_normalVectors");
}

void GeneralShader::GetAllUniformLocations()
{
	m_transformationMatrix_Location = GetUniformLocation("transformationMatrix");
	m_projectionMatrix_Location = GetUniformLocation("projectionMatrix");
	m_viewMatrix_Location = GetUniformLocation("viewMatrix");
}
