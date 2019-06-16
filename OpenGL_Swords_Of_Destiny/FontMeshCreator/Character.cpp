#include "../pch.h"
#include "Character.hpp"


Character::Character(int id, double xTextureCoord, double yTextureCoord, double xTexSize, double yTexSize, double xOffset, double yOffset, double sizeX, double sizeY, double xAdvance)
{
	_textureId = id;
	_xTextureCoord = xTextureCoord;
	_yTextureCoord = yTextureCoord;
	_xOffset = xOffset;
	_yOffset = yOffset;
	_sizeX = sizeX;
	_sizeY = sizeY;
	_xMaxTextureCoord = xTexSize + xTextureCoord;
	_yMaxTextureCoord = yTexSize + yTextureCoord;
	_xAdvance = xAdvance;
}
