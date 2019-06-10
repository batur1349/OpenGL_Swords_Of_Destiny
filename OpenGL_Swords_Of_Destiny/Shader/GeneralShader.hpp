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
	void LoadLight(Light& light);
protected:
	// Functions
	void BindAttributes();
	void GetAllUniformLocations();
private:
	// Variables
	GLuint m_transformationMatrix_Location, m_projectionMatrix_Location, m_viewMatrix_Location
		, m_lightPosition_Location, m_lightColor_Location, m_selected_Location;
};
#endif // !GENERALSHADER_HPP