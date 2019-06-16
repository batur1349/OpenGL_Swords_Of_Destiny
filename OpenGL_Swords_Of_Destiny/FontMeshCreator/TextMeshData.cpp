#include "../pch.h"
#include "TextMeshData.hpp"


TextMeshData::TextMeshData(std::vector<glm::vec2> vertexPositions, std::vector<glm::vec2> textureCoords)
{
	_vertexPositions = vertexPositions;
	_textureCoords = textureCoords;
}
