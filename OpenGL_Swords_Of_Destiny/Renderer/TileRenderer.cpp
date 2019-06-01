#include "../pch.h"
#include "TileRenderer.hpp"


TileRenderer::TileRenderer(TileShader& shader, const glm::mat4& projectionMatrix)
	: m_shader(shader)
{
	// Create the projection matrix using GLM and load it into the shader
	m_shader.Start();
	m_shader.LoadProjectionMatrix(projectionMatrix);
	m_shader.Stop();
}

void TileRenderer::RenderTiles(std::map<TexturedObject, std::vector<Tile>, TileTextureObjectCompare>& tiles)
{
	// Loop through the mapObjects
	for (auto& mapObject : tiles)
	{
		// key.first = TexturedModel, key.second = std::vector<Entity>
		// Bind the texturedModel's texture
		BindTexturedObject(mapObject.first);
		// Render all of the entities in the container
		for (auto& tile : mapObject.second)
			RenderTile(tile);
		// Unbind the texturedModel
		UnbindTexturedModel();
	}
}

void TileRenderer::EnableCulling()
{
	// Don't draw faces we can't see
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void TileRenderer::DisableCulling()
{
	glDisable(GL_CULL_FACE);
}

void TileRenderer::BindTexturedObject(TexturedObject texturedObject)
{
	// Bind the models vertex array object id so we can render it
	glBindVertexArray(texturedObject.GetModelObject().GetVaoID());

	// Enable the attrib arrays 0 - Position, 1 - TextureCoords, 2 - Normals
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// Activate an OpenGL texture unit and tell it where the texture is
	glActiveTexture(GL_TEXTURE0);

	// Bind the texturedModel's texture
	glBindTexture(GL_TEXTURE_2D, texturedObject.GetModelTexture().GetTextureID());
}

void TileRenderer::UnbindTexturedModel()
{
	// Enable the cullface again
	EnableCulling();

	// Disable the attrib arrays
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void TileRenderer::RenderTile(Tile& tile)
{
	// Load the transformation matrix into the shader
	m_shader.LoadTransformationMatrix(Maths::CreateTransformationMatrix(tile.GetPosition(), glm::vec3(0), glm::vec3(1)));

	// Draw the model
	glDrawElements(GL_TRIANGLES, tile.GetTexturedObject().GetModelObject().GetIndiceCount(), GL_UNSIGNED_INT, 0);
}
