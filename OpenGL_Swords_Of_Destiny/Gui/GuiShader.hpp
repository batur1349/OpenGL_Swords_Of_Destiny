#ifndef GUISHADER_HPP
#define GUISHADER_HPP

#include "../Shader/ShaderProgram.hpp"

class GuiShader : public ShaderProgram
{
public:
	// Constructor
	GuiShader();

	// Functions
	void LoadTransformationMatrix(glm::mat4 matrix);
protected:
	void BindAttributes();
	void GetAllUniformLocation();
private:
	GLuint _location_transformationMatrix;
};

#endif // !GUISHADER_HPP