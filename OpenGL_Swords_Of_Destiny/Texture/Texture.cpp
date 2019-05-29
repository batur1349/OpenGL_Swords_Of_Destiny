#include "../pch.h"
#include "Texture.hpp"

Texture::Texture(GLuint id)
{
	m_textureID = id;
}

GLuint& Texture::GetTextureID()
{
	return m_textureID;
}
