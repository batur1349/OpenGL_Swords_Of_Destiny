#ifndef FONTTYPE_HPP
#define FONTTYPE_HPP

#include "TextMeshCreator.hpp"
class TextMeshCreator;
#include "GUIText.hpp"
class GUIText;

class FontType
{
public:
	// Constructor
	FontType(GLuint textureAtlas, const std::string& fontFile);

	// Getters
	inline GLuint& GetTextureAtlas() { return _textureAtlas; }
	TextMeshData LoadText(GUIText text);
private:
	GLuint _textureAtlas;
	TextMeshCreator _loader;
};

#endif // !FONTTYPE_HPP