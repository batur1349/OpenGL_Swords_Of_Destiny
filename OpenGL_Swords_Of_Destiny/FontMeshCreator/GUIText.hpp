#ifndef GUITEXT_HPP
#define GUITEXT_HPP

#include "FontType.hpp"
class FontType;

class GUIText
{
public:
	// Constructor
	GUIText(std::string text, float fontSize, FontType font, glm::vec2 position, float maxLineLength, bool centered);

	// Getters
	inline FontType& GetFont() { return _font; }
	inline glm::vec3& GetColor() { return _color; }
	inline int& GetNumberOfLines() { return _numberOfLines; }
	inline glm::vec2& GetPosition() { return _position; }
	inline GLuint& GetMesh() { return _textMeshVao; }
	inline int& GetVertexCount() { return _vertexCount; }
	inline float& GetFontSize() { return _fontSize; }
	inline bool& isCentered() { return _centerText; }
	inline float& GetMaxLineSize() { return _lineMaxSize; }
	inline std::string& GetTextString() { return _textString; }

	// Setters
	void SetColor(const glm::vec3& color) { _color = color; }
	void SetMeshInfo(const GLuint& vao, const int& vertexCount);
	void SetNumberOfLines(const int& number) { _numberOfLines = number; }
private:
	std::string _textString;
	float _fontSize;

	GLuint _textMeshVao;
	int _vertexCount;
	glm::vec3 _color;

	glm::vec2 _position;
	float _lineMaxSize;
	int _numberOfLines;

	FontType& _font;
	bool _centerText = false;
};

#endif // !GUITEXT_HPP