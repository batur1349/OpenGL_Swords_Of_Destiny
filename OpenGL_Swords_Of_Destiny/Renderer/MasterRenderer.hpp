#ifndef MASTERRENDERER_HPP
#define MASTERRENDERER_HPP

#include "../Loader/Loader.hpp"
#include "../Shader/GeneralShader.hpp"
#include "../Entity/Entity.hpp"
#include "../Maths/Maths.hpp"

#include "TileRenderer.hpp"
#include "EntityRenderer.hpp"

class MasterRenderer
{
public:
	// Constructor and ~Destructor
	MasterRenderer(float aspect, Loader& loader);
	virtual ~MasterRenderer();

	// Functions
	void Prepare();
	void Render(std::vector<Entity>& entities, std::vector<Tile>& terrains, ThirdPersonCamera& camera);
	void ConstructEntityBatch(Entity& entity);
	void ConstructTerrainBatch(Tile& tile);

	// Getters
	inline glm::mat4& GetProjectionMatrix() { return m_projectionMatrix; }
private:
	// Variables
	const float m_FOV = 70;
	const float m_NEAR_PLANE = 0.1f;
	const float m_FAR_PLANE = 1000;
	const float RED = 0.5444f, GREEN = 0.62f, BLUE = 0.69f;
	glm::mat4 m_projectionMatrix;

	GeneralShader m_shader;

	TileShader m_tileShader;
	TileRenderer m_tileRenderer;

	EntityRenderer m_entityRenderer;

	// Containers
	std::vector<Tile> m_terrains;
	std::map<TexturedObject, std::vector<Entity>, TextureObjectCompare> m_entities;
};

#endif // !MASTERRENDERER_HPP