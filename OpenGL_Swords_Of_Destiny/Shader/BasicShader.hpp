#ifndef BASICSHADER_HPP
#define BASICSHADER_HPP

#include "Shader.hpp"
#include "../Entity/Camera.hpp"
#include "../Toolbox/Maths.hpp"
#include "../Entity/Light.hpp"

class BasicShader : public Shader
{
public:
	// Constructor
	BasicShader();
	BasicShader(const std::string& fileName);

	// Functions
	void LoadTransformationMatrix(glm::mat4 matrix);
	void LoadProjectionMatrix(glm::mat4 matrix);
	void LoadViewMatrix(Camera camera);
	void LoadLightVariables(Light light);
protected:
	// Functions
	void BindAttributes();
	void GetAllUniformLocations();
private:
	// Variables
	GLuint _location_transformationMatrix, _location_projectionMatrix, _location_viewMatrix,
		_location_lightPosition, _location_lightColor;
};

#endif // !BASICSHADER_HPP