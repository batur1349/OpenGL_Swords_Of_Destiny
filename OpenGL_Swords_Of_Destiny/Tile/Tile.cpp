#include "../pch.h"
#include "Tile.hpp"


Tile::Tile(TexturedObject& texObj, const glm::vec3& position)
	: m_texturedObject(texObj)
{
	m_position = position;
}

Tile::Tile(const std::string& texName, const glm::vec3& position, Loader& loader)
	: m_texturedObject(Object(loader.LoadToVAO(GenerateVertices(), GenerateUvs(), GenerateNormals(), GenerateIndices()))
		, Texture(loader.LoadTexture2D(texName)))
{
	m_position = position;
}

Tile::~Tile()
{

}

std::vector<glm::vec3> Tile::GenerateVertices()
{
	return std::vector<glm::vec3> { glm::vec3(-1, 0, -1), glm::vec3(-1, 0, 1), glm::vec3(1, 0, 1), glm::vec3(1, 0, -1) };
}

std::vector<glm::vec2> Tile::GenerateUvs()
{
	return std::vector<glm::vec2> { glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(1, 0), glm::vec2(1, 1) };
}

std::vector<glm::vec3> Tile::GenerateNormals()
{
	return std::vector<glm::vec3> { glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0) };
}

std::vector<int> Tile::GenerateIndices()
{
	return std::vector<int> { 0, 1, 2, 2, 3, 0 };
}
