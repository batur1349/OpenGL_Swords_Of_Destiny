#ifndef FONTSHADER_HPP
#define FONTSHADER_HPP

#include "ShaderProgram.hpp"

class FontShader : public ShaderProgram
{
public:
	// Constructor
	FontShader();

	// Functions
	void LoadTextColor(const glm::vec3& color);
	void LoadProjectionMatrix(const glm::mat4& matrix);
protected:
	// Functions
	void BindAttributes();
	void GetAllUniformLocations();
private:
	// Variables
	GLuint m_projection_Location, m_textColor_Location;
};

#endif // !FONTSHADER_HPP