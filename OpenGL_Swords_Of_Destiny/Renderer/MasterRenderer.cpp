#include "../pch.h"
#include "MasterRenderer.hpp"


MasterRenderer::MasterRenderer(float aspect, Loader& loader)
	: m_projectionMatrix(glm::perspective(glm::radians(m_FOV), aspect, m_NEAR_PLANE, m_FAR_PLANE)),
	m_entityRenderer(m_shader, m_projectionMatrix), m_tileRenderer(m_tileShader, m_projectionMatrix)
	, m_guiRenderer(loader)
{
	// Enable the depty test
	glEnable(GL_DEPTH_TEST);

	// Enable the back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

MasterRenderer::~MasterRenderer()
{

}

void MasterRenderer::Prepare()
{
	// Clear the screen with this color
	glClearColor(RED, GREEN, BLUE, 1.0f);
	// Clear the previous buffered colors
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::Render(std::vector<Entity>& entities, std::vector<Tile>& tiles, std::vector<GuiTexture>& guis, Light& light,
	ThirdPersonCamera& camera, std::map<std::string, Texture>& tileTextures)
{
	for (auto& entity : entities)
		ConstructEntityBatch(entity);
	for (auto& tile : tiles)
		ConstructTileBatch(tile);

	// Prepare the screen
	Prepare();

	// Calculate the frustum
	if (m_oldViewMatrix != camera.GetViewMatrix())
	{
		m_oldViewMatrix = camera.GetViewMatrix();
		m_frustum.CalculateFrustumPlanes(camera.GetViewMatrix());
	}

	// Activate the shader
	m_shader.Start();

	// Load shader parameters
	m_shader.LoadViewMatrix(camera);

	// Load light parameters
	m_shader.LoadLight(light);

	// Render all of the entities
	m_entityRenderer.RenderEntities(m_entities, m_frustum);

	// Deactivate shader and clear entities
	m_shader.Stop(); m_entities.clear();

	// Start the terrain shader
	m_tileShader.Start();

	// Load terrain shader parameters
	m_tileShader.LoadViewMatrix(camera);

	// Load light parameters
	m_tileShader.LoadLight(light);

	// Render all of the terrains
	m_tileRenderer.RenderTiles(m_tiles, m_frustum, tileTextures);

	// Stop terrain shader and clear terrains
	m_tileShader.Stop(); m_tiles.clear();

	// Render the Gui Textures
	m_guiRenderer.Render(guis);
}

void MasterRenderer::ConstructEntityBatch(Entity& entity)
{
	// Get the textured model
	TexturedObject texturedObject = entity.GetTexturedObject();

	// If the texturedmodel is in the map this will do nothing
	// If it is not in the map it will insert it
	m_entities.insert(std::make_pair(texturedObject, std::vector<Entity>()));

	// Add the entity to the entities list
	m_entities.find(texturedObject)->second.push_back(entity);
}

void MasterRenderer::ConstructTileBatch(Tile& tile)
{
	// Get the textured model
	TexturedObject texturedObject = tile.GetTexturedObject();

	// If the texturedmodel is in the map this will do nothing
	// If it is not in the map it will insert it
	m_tiles.insert(std::make_pair(texturedObject, std::vector<Tile>()));

	// Add the entity to the entities list
	m_tiles.find(texturedObject)->second.push_back(tile);
}
