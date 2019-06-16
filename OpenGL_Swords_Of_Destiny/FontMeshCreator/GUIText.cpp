#include "../pch.h"
#include "GUIText.hpp"


GUIText::GUIText(std::string text, float fontSize, FontType font, glm::vec2 position, float maxLineLength, bool centered)
	: _font(font)
{
	_textString = text;
	_fontSize = fontSize;
	_position = position;
	_lineMaxSize = maxLineLength;
	_centerText = centered;

	_color = glm::vec3(0.0f);
}

void GUIText::SetMeshInfo(const GLuint& vao, const int& vertexCount)
{
	_textMeshVao = vao;
	_vertexCount = vertexCount;
}
