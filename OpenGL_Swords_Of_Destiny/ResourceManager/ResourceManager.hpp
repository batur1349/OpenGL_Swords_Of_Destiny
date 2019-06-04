#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include "../Entity/TexturedObject.hpp"
#include "../Loader/Loader.hpp"
#include "../Entity/Entity.hpp"
#include "../Tile/Tile.hpp"
#include "../Gui/GuiTexture.hpp"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	const TexturedObject& GetLowPolyTreeTexturedObject() { return *m_lowPolyTreeTexturedObject; }
	const TexturedObject& GetTileTexturedObject() { return *m_tileTexturedObject; }

	const std::vector<Tile>& GenerateTilemap();
	const std::vector<Entity>& GenerateEntities();
	const std::vector<GuiTexture>& GenerateGuiTextures();
private:
	Loader m_loader;
	std::vector<Tile> m_tiles;
	std::vector<Entity> m_entities;
	std::vector<GuiTexture> m_guiTextures;

	TexturedObject* m_lowPolyTreeTexturedObject;
	TexturedObject* m_tileTexturedObject;
};

#endif // !RESOURCEMANAGER_HPP