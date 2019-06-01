#include "../pch.h"
#include "TileRenderer.hpp"
#include "../Maths/Maths.hpp"


TileRenderer::TileRenderer(TileShader& shader, const glm::mat4& projectionMatrix)
	: m_shader(shader)
{
	// Create the projection matrix using GLM and load it into the shader
	m_shader.Start();
	m_shader.LoadProjectionMatrix(projectionMatrix);
	m_shader.Stop();
}

void TileRenderer::Render(std::vector<Tile>& tiles)
{
	for (auto& tile : tiles)
	{
		PrepareTile(tile);
		LoadModelMatrix(tile);
		UnbindTexturedModel();
	}
}

void TileRenderer::PrepareTile(Tile& tile)
{
	// Get the BaseModel from the TexturedModel
	Object object = tile.GetBaseModel();

	// Bind the models vertex array object id so we can render it
	glBindVertexArray(object.GetVaoID());

	// Enable the attrib arrays 0 - Position, 1 - TextureCoords, 2 - Normals
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// Bind the terrain textures
	BindTextures(tile);
}

void TileRenderer::UnbindTexturedModel()
{
	// Disable the attrib arrays
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void TileRenderer::LoadModelMatrix(Tile& tile)
{
	// Load the transformation matrix into the shader
	m_shader.LoadTransformationMatrix(Maths::CreateTransformationMatrix(glm::vec3(tile.GetX(), 0.0f, tile.GetZ())
		, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
	// Draw the model
	glDrawElements(GL_TRIANGLES, tile.GetBaseModel().GetIndiceCount(), GL_UNSIGNED_INT, 0);
}

void TileRenderer::BindTextures(Tile& tile)
{
	// Activate an OpenGL texture unit and tell it where the texture is
	glActiveTexture(GL_TEXTURE0);

	// Bind the texturedModel's texture
	glBindTexture(GL_TEXTURE_2D, tile.GetTextureID());
}
