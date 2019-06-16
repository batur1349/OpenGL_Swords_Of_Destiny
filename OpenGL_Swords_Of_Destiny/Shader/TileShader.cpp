#include "../pch.h"
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

void TileShader::LoadSelected(const bool& selected)
{
	if (selected)
		LoadFloat(m_selected_Location, 1);
	else
		LoadFloat(m_selected_Location, 0);
}

void TileShader::LoadUseFog(const bool& usefog)
{
	if (usefog)
		LoadFloat(m_useFog_Location, 1);
	else
		LoadFloat(m_useFog_Location, 0);
}

void TileShader::ConnectTextureUnits()
{
	LoadInt(m_texture_Location, 0);
	LoadInt(m_selectedTile_Location, 1);
	LoadInt(m_bloodTile_Location, 2);
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
	m_selected_Location = GetUniformLocation("selected");
	m_texture_Location = GetUniformLocation("textureSampler");
	m_selectedTile_Location = GetUniformLocation("selectedSampler");
	m_bloodTile_Location = GetUniformLocation("bloodSampler");
	m_useFog_Location = GetUniformLocation("useFog");
}
