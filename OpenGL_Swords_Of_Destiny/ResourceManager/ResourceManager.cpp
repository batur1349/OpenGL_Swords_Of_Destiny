#include "../pch.h"
#include "ResourceManager.hpp"


ResourceManager::ResourceManager()
{
	Object lowPolyTreeObject = m_loader.LoadAssimpObjFile("lowPolyTree");
	Texture lowPolyTreeTexture = m_loader.LoadTexture2D("lowPolyTree");
	m_lowPolyTreeTexturedObject = new TexturedObject(lowPolyTreeObject, lowPolyTreeTexture);

	std::vector<glm::vec3> tileVert = { glm::vec3(-1, 0, -1), glm::vec3(-1, 0, 1), glm::vec3(1, 0, 1), glm::vec3(1, 0, -1) };
	std::vector<glm::vec2> tileUvs = { glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(1, 0), glm::vec2(1, 1) };
	std::vector<glm::vec3> tileNormals = { glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0) };
	std::vector<int> tileIndices = { 0, 1, 2, 2, 3, 0 };
	Object tileObject = m_loader.LoadToVAO(tileVert, tileUvs, tileNormals, tileIndices);
	Texture tileTexture = m_loader.LoadTexture2D("grass2");
	m_tileTexturedObject = new TexturedObject(tileObject, tileTexture);
}

ResourceManager::~ResourceManager()
{
	delete m_lowPolyTreeTexturedObject;
	delete m_tileTexturedObject;
}

const std::vector<Tile>& ResourceManager::GenerateTilemap()
{
	float offset = 2, adet = 40;
	for (float i = 0; i < adet; i++)
	{
		for (float j = 0; j < adet; j++)
		{
			m_tiles.push_back(Tile(*m_tileTexturedObject, glm::vec3(i * offset, 0, j * offset)));
		}
	}
	m_tiles.at(0).SetSelected(true);

	return m_tiles;
}

const std::vector<Entity>& ResourceManager::GenerateEntities()
{
	int x, y, z;
	for (int i = 0; i < 60; i++)
	{
		x = rand() % 80;
		y = 0;
		z = rand() % 80;

		m_entities.emplace_back(*m_lowPolyTreeTexturedObject, glm::vec3(x, y, z), glm::vec3(0), glm::vec3(0.1));
	}

	return m_entities;
}
