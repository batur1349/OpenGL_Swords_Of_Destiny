#ifndef TILESHADER_HPP
#define TILESHADER_HPP

#include "ShaderProgram.hpp"
#include "../Entity/ThirdPersonCamera.hpp"

class TileShader : public ShaderProgram
{
public:
	// Constructor
	TileShader();

	// Functions
	void LoadTransformationMatrix(const glm::mat4& matrix);
	void LoadProjectionMatrix(const glm::mat4& matrix);
	void LoadViewMatrix(ThirdPersonCamera& camera);
protected:
	// Functions
	void BindAttributes();
	void GetAllUniformLocations();
private:
	// Variables
	GLuint m_transformationMatrix_Location, m_projectionMatrix_Location, m_viewMatrix_Location;
};

#endif // !TILESHADER_HPP