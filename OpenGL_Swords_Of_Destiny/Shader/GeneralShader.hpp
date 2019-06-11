#ifndef GENERALSHADER_HPP
#define GENERALSHADER_HPP

#include "ShaderProgram.hpp"
#include "../Entity/ThirdPersonCamera.hpp"
#include "../Entity/Light.hpp"

class GeneralShader : public ShaderProgram
{
public:
	// Constructor
	GeneralShader();

	// Functions
	void LoadTransformationMatrix(const glm::mat4& matrix);
	void LoadProjectionMatrix(const glm::mat4& matrix);
	void LoadViewMatrix(ThirdPersonCamera& camera);
	void LoadSelected(const bool& value);
	void LoadUseFog(const bool& fog);
	void LoadShineVariables(const float& shine, const float& reflect);
	void LoadFakeLightningVariable(const bool& useFakeLightning);
	void LoadLights(std::vector<Light>& lights);
protected:
	// Functions
	void BindAttributes();
	void GetAllUniformLocations();
private:
	// Variables
	static const int MAX_LIGHTS = 8;
	GLuint m_transformationMatrix_Location, m_projectionMatrix_Location, m_viewMatrix_Location
		, m_lightPosition_Location[MAX_LIGHTS], m_lightColor_Location[MAX_LIGHTS], m_selected_Location;
	GLuint m_shineDamper_Location, m_reflectivity_Location, m_fakeLightning_Location;
	GLuint m_useFog_Location;
};
#endif // !GENERALSHADER_HPP