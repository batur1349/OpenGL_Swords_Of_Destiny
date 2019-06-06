#include "../pch.h"
#include "ResourceManager.hpp"


ResourceManager::ResourceManager()
{
	// LOWPOLYTREE
	Object lowPolyTreeObject = m_loader.LoadAssimpObjFile("lowPolyTree");
	Texture lowPolyTreeTexture = m_loader.LoadTexture2D("lowPolyTree");
	m_lowPolyTreeTexturedObject = new TexturedObject(lowPolyTreeObject, lowPolyTreeTexture);
	// STALL
	Object stallObject = m_loader.LoadAssimpObjFile("stall");
	Texture stallTexture = m_loader.LoadTexture2D("stall");
	m_stallTexturedObject = new TexturedObject(stallObject, stallTexture);

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
	delete m_stallTexturedObject;
	delete m_tileTexturedObject;
}

const std::vector<Tile>& ResourceManager::GenerateTilemap()
{
	float offset = 2, count = 100;

#ifdef _DEBUG
	count = 20;
#else
	count = 80;
#endif // _DEBUG

	for (float i = 0; i < count; i++)
	{
		for (float j = 0; j < count; j++)
		{
			m_tiles.push_back(Tile(*m_tileTexturedObject, glm::vec3(i * offset, 0, j * offset)));
		}
	}
	m_tiles.at(0).SetSelected(true);

	return m_tiles;
}

const std::vector<Entity>& ResourceManager::GenerateEntities()
{
	int x, y, z, type;
	float scx, scy, scz;
	for (int i = 0; i < 60; i++)
	{
		type = rand() % 2;
		x = rand() % 80;
		y = 0;
		z = rand() % 80;

		scx = 15.0f / (float)100;
		scy = (float)(rand() % 19 + 10) / (float)100;
		scz = scx;

		if (type == 0)
			m_entities.emplace_back(*m_lowPolyTreeTexturedObject, glm::vec3(x, y, z), glm::vec3(0), glm::vec3(scx, scy, scz));
		else if (type == 1)
			m_entities.emplace_back(*m_stallTexturedObject, glm::vec3(x, y, z), glm::vec3(0), glm::vec3(0.25));
	}

	return m_entities;
}

const std::vector<GuiTexture>& ResourceManager::GenerateGuiTextures()
{
	GuiTexture gui(m_loader.LoadTexture2D("health"), glm::vec2(-0.75, 0.90), glm::vec2(0.25, 0.25));

	m_guiTextures.push_back(gui);

	return m_guiTextures;
}
