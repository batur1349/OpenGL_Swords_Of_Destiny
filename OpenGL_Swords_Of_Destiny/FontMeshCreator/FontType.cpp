#include "../pch.h"
#include "FontType.hpp"


FontType::FontType(GLuint textureAtlas, const std::string& fontFile)
	: _loader(fontFile)
{

}

TextMeshData FontType::LoadText(GUIText text)
{
	return _loader.CreateTextMesh(text);
}
