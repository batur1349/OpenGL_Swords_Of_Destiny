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

void GeneralShader::LoadSelected(const bool& value)
{
	if (value)
		LoadFloat(m_selected_Location, 1.0f);
	else
		LoadFloat(m_selected_Location, 0.0f);
}

void GeneralShader::LoadUseFog(const bool& fog)
{
	if (fog)
		LoadFloat(m_useFog_Location, 1);
	else
		LoadFloat(m_useFog_Location, 0);
}

void GeneralShader::LoadShineVariables(const float& shine, const float& reflect)
{
	LoadFloat(m_shineDamper_Location, shine);
	LoadFloat(m_reflectivity_Location, reflect);
}

void GeneralShader::LoadFakeLightningVariable(const bool& useFakeLightning)
{
	if (useFakeLightning)
		LoadFloat(m_fakeLightning_Location, 1);
	else
		LoadFloat(m_fakeLightning_Location, 0);
}

void GeneralShader::LoadLights(std::vector<Light>& lights)
{
	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		if (i < lights.size())
		{
			LoadVector3F(m_lightPosition_Location[i], lights.at(i).GetPosition());
			LoadVector3F(m_lightColor_Location[i], lights.at(i).GetColor());
		}
		else
		{
			LoadVector3F(m_lightPosition_Location[i], glm::vec3(0.0f));
			LoadVector3F(m_lightColor_Location[i], glm::vec3(0.0f));
		}
	}
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
	m_selected_Location = GetUniformLocation("selected");
	m_shineDamper_Location = GetUniformLocation("shineDamper");
	m_reflectivity_Location = GetUniformLocation("reflectivity");
	m_fakeLightning_Location = GetUniformLocation("fakeLightning");
	m_useFog_Location = GetUniformLocation("useFog");

	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		m_lightPosition_Location[i] = GetUniformLocation("lightPosition[" + std::to_string(i) + "]");
		m_lightColor_Location[i] = GetUniformLocation("lightColor[" + std::to_string(i) + "]");
	}
}
