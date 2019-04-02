#include "../pch.h"
#include "Texture.hpp"


Texture::Texture(GLuint id)
{
	_textureID = id;
}

const GLuint & Texture::GetTextureID() const
{
	return _textureID;
}