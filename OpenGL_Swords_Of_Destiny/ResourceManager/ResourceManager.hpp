#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include "../Entity/Entity.hpp"
#include "../Tile/Tile.hpp"
#include "../Gui/GuiTexture.hpp"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	const TexturedObject& GetLowPolyTreeTexturedObject() { return *m_lowPolyTreeTexturedObject; }
	const TexturedObject& GetStallTextuedObject() { return *m_stallTexturedObject; }
	const TexturedObject& GetTileTexturedObject() { return *m_tileTexturedObject; }

	const std::vector<Tile>& GenerateTilemap();
	const std::vector<Entity>& GenerateEntities();
	const std::vector<GuiTexture>& GenerateGuiTextures();
	const std::map<std::string, Texture>& GenerateTileTextures();
	const std::map<GLuint, std::vector<glm::vec3>>& GetObjectVertices() { return m_objectVertices; }
	const std::map<GLuint, std::pair<glm::vec3, glm::vec3>>& GetObjectBounds() { return m_objectBounds; }
private:
	Loader m_loader;
	std::vector<Tile> m_tiles;
	std::vector<Entity> m_entities;
	std::vector<GuiTexture> m_guiTextures;
	std::map<std::string, Texture> m_tileTextures;
	void GetObjectVertices(const std::string& fileName, const GLuint& id);
	std::map<GLuint, std::vector<glm::vec3>> m_objectVertices;
	void CalculateObjectBounds();
	std::map<GLuint, std::pair<glm::vec3, glm::vec3>> m_objectBounds;

	TexturedObject* m_lowPolyTreeTexturedObject, * m_tileTexturedObject, * m_stallTexturedObject;
};

#endif // !RESOURCEMANAGER_HPP