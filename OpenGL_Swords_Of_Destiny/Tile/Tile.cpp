#include "../pch.h"
#include "Tile.hpp"


Tile::Tile(const TexturedObject& texObj, const glm::vec3& position, const glm::vec3& endPosition)
	: m_texturedObject(texObj)
{
	m_position = position;
	m_endPosition = endPosition;
	m_selected = false;
}

Tile::~Tile()
{

}

std::vector<glm::vec3> Tile::GenerateVertices()
{
	return std::vector<glm::vec3> { glm::vec3(0, 0, 1), glm::vec3(1, 0, 1), glm::vec3(1, 0, 0), glm::vec3(0, 0, 0) };
}

std::vector<glm::vec2> Tile::GenerateUvs()
{
	return std::vector<glm::vec2> { glm::vec2(1, 0), glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(1, 1) };
}

std::vector<glm::vec3> Tile::GenerateNormals()
{
	return std::vector<glm::vec3> { glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0) };
}

std::vector<int> Tile::GenerateIndices()
{
	return std::vector<int> { 0, 1, 2, 2, 3, 0 };
}
