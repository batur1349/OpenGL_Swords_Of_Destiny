#ifndef MASTERRENDERER_HPP
#define MASTERRENDERER_HPP

#include "../Entity/Entity.hpp"
#include "EntityRenderer.hpp"
#include "../Shader/TileShader.hpp"
#include "TileRenderer.hpp"
#include "../Gui/GuiRenderer.hpp"

class MasterRenderer
{
public:
	// Constructor and ~Destructor
	MasterRenderer(float aspect, Loader& loader);
	virtual ~MasterRenderer();

	// Functions
	void Prepare();
	void Render(std::vector<Entity>& entities, std::vector<Tile>& tiles, std::vector<GuiTexture>& guis, Light& light, ThirdPersonCamera& camera, Texture selectedTexture);
	void ConstructEntityBatch(Entity& entity);
	void ConstructTileBatch(Tile& tile);

	// Getters
	inline glm::mat4& GetProjectionMatrix() { return m_projectionMatrix; }
private:
	// Variables
	const float m_FOV = 60;
	const float m_NEAR_PLANE = 1.0f;
	const float m_FAR_PLANE = 500.0f;
	const float RED = 0.5444f, GREEN = 0.62f, BLUE = 0.69f;
	glm::mat4 m_projectionMatrix;

	GeneralShader m_shader;
	TileShader m_tileShader;
	TileRenderer m_tileRenderer;

	EntityRenderer m_entityRenderer;

	Frustum m_frustum;

	GuiRenderer m_guiRenderer;

	// Containers
	glm::mat4 m_oldViewMatrix;
	std::vector<GuiTexture> m_guiTextures;
	std::map<TexturedObject, std::vector<Tile>, TileTextureObjectCompare> m_tiles;
	std::map<TexturedObject, std::vector<Entity>, TextureObjectCompare> m_entities;
};

#endif // !MASTERRENDERER_HPP