#ifndef FONT_HPP
#define FONT_HPP

#include "TextShader.hpp"

struct Character
{
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};

class Font
{
public:
	Font(const std::string& fontName, const int& fontSize);

	void RenderText(const std::string& text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
private:
	void Prepare();
	void Finish();

	GLuint VAO, VBO;
	TextShader shader;
	glm::mat4 projection;
	std::map<GLchar, Character> Characters;
};

#endif // !FONT_HPP