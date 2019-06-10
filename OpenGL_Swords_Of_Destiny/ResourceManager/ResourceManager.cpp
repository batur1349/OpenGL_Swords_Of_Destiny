#include "../pch.h"
#include "ResourceManager.hpp"


ResourceManager::ResourceManager()
{
	// LOWPOLYTREE
	Object lowPolyTreeObject = m_loader.LoadAssimpObjFile("lowPolyTree");
	Texture lowPolyTreeTexture = m_loader.LoadTexture2D("lowPolyTree");
	m_lowPolyTreeTexturedObject = new TexturedObject(lowPolyTreeObject, lowPolyTreeTexture);

	GetObjectVertices("lowPolyTree", lowPolyTreeObject.GetVaoID());
	// STALL
	Object stallObject = m_loader.LoadAssimpObjFile("stall");
	Texture stallTexture = m_loader.LoadTexture2D("stall");
	m_stallTexturedObject = new TexturedObject(stallObject, stallTexture);

	GetObjectVertices("stall", stallObject.GetVaoID());

	std::vector<glm::vec3> tileVert = { glm::vec3(-1, 0, -1), glm::vec3(-1, 0, 1), glm::vec3(1, 0, 1), glm::vec3(1, 0, -1) };
	std::vector<glm::vec2> tileUvs = { glm::vec2(1, 0), glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(1, 1) };
	std::vector<glm::vec3> tileNormals = { glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0) };
	std::vector<int> tileIndices = { 0, 1, 2, 2, 3, 0 };
	Object tileObject = m_loader.LoadToVAO(tileVert, tileUvs, tileNormals, tileIndices);
	Texture tileTexture = m_loader.LoadTexture2D("grass2");
	m_tileTexturedObject = new TexturedObject(tileObject, tileTexture);

	m_objectVertices[tileObject.GetVaoID()] = tileVert;

	CalculateObjectBounds();
}

ResourceManager::~ResourceManager()
{
	delete m_lowPolyTreeTexturedObject;
	delete m_stallTexturedObject;
	delete m_tileTexturedObject;
}

const std::vector<Tile>& ResourceManager::GenerateTilemap()
{
	float offset = 2, count = 0;

#ifdef _DEBUG
	count = 10;
#else
	count = 80;
#endif // _DEBUG

	for (float i = 0; i < count; i++)
	{
		for (float j = 0; j < count; j++)
		{
			m_tiles.push_back(Tile(*m_tileTexturedObject,								// Textured object
				glm::vec3((i * offset) + 1.0f, 0, (j * offset) + 1.0f),					// Start Position
				glm::vec3(((i + 1) * offset) + 1.0f, 0, ((j + 1) * offset) + 1.0f))		// End Position
			);
		}
	}

	return m_tiles;
}

const std::vector<Entity>& ResourceManager::GenerateEntities()
{
	int x, y, z, type, adet;
	float scx, scy, scz;

#ifdef _DEBUG
	adet = 1;
#else
	adet = 80;
#endif // _DEBUG

	for (int i = 0; i < adet; i++)
	{
		type = rand() % 2;
		x = rand() % 80;
		y = 0;
		z = rand() % 80;

		scx = 15.0f / (float)100;
		scy = (float)(rand() % 19 + 10) / (float)100;
		scz = scx;

		type = 0;
		if (type == 0)
			m_entities.emplace_back(*m_lowPolyTreeTexturedObject, glm::vec3(x, y, z), glm::vec3(0), glm::vec3(scx, scy, scz), m_objectBounds.at(m_lowPolyTreeTexturedObject->GetModelObject().GetVaoID()));
		else if (type == 1)
			m_entities.emplace_back(*m_stallTexturedObject, glm::vec3(x, y, z), glm::vec3(0), glm::vec3(0.25), m_objectBounds.at(m_stallTexturedObject->GetModelObject().GetVaoID()));
	}

	return m_entities;
}

const std::vector<GuiTexture>& ResourceManager::GenerateGuiTextures()
{
	GuiTexture gui(m_loader.LoadTexture2D("health"), glm::vec2(-0.75, 0.90), glm::vec2(0.25, 0.25));

	m_guiTextures.push_back(gui);

	return m_guiTextures;
}

const std::map<std::string, Texture>& ResourceManager::GenerateTileTextures()
{
	Texture selectedTexture = m_loader.LoadTexture2D("tile_selected");
	m_tileTextures.insert(std::pair<std::string, Texture>("tile_selected", selectedTexture));

	Texture bloodTexture = m_loader.LoadTexture2D("tile_blood");
	m_tileTextures.insert(std::pair<std::string, Texture>("tile_blood", bloodTexture));

	return m_tileTextures;
}

void ResourceManager::GetObjectVertices(const std::string& fileName, const GLuint& id)
{
	// Actual importer
	Assimp::Importer importer;

	// Static containers
	std::vector<glm::vec3> vertices;

	// Actual path
	std::string path = "../Objects/" + fileName + ".obj";

	const aiScene* scene = importer.ReadFile(path, aiProcess_JoinIdenticalVertices | aiProcess_SortByPType | aiProcess_ConvertToLeftHanded);
	if (!scene)
	{
		fprintf(stderr, importer.GetErrorString());
		getchar();
	}

	const aiMesh* mesh = scene->mMeshes[0];
	// If you want to load more than one mesh than change it with a for loop or etc.
	// In obj files there is only 1 mesh

	// Fill vertices positions
	vertices.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		aiVector3D pos = mesh->mVertices[i];
		vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
	}

	m_objectVertices[id] = vertices;
}

void ResourceManager::CalculateObjectBounds()
{
	glm::vec3 min, max;
	int size = m_objectVertices.size();

	for (int i = 1; i <= size; i++)
	{
		min = m_objectVertices[i].at(0);
		max = m_objectVertices[i].at(0);

		for (int j = 0; j < m_objectVertices.at(i).size(); j++)
		{
			if (min.x > m_objectVertices.at(i).at(j).x)
				min.x = m_objectVertices.at(i).at(j).x;
			if (min.y > m_objectVertices.at(i).at(j).y)
				min.y = m_objectVertices.at(i).at(j).y;
			if (min.z > m_objectVertices.at(i).at(j).z)
				min.z = m_objectVertices.at(i).at(j).z;

			if (max.x < m_objectVertices.at(i).at(j).x)
				max.x = m_objectVertices.at(i).at(j).x;
			if (max.y < m_objectVertices.at(i).at(j).y)
				max.y = m_objectVertices.at(i).at(j).y;
			if (max.z < m_objectVertices.at(i).at(j).z)
				max.z = m_objectVertices.at(i).at(j).z;
		}

		m_objectBounds[i] = std::pair<glm::vec3, glm::vec3>(min, max);
	}
}
