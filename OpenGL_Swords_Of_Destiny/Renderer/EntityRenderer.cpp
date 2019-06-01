#include "../pch.h"
#include "EntityRenderer.hpp"


EntityRenderer::EntityRenderer(GeneralShader& shader, const glm::mat4& projectionMatrix)
	: m_shader(shader)
{
	// Create the projection matrix using GLM and load it into the shader
	m_shader.Start();
	m_shader.LoadProjectionMatrix(projectionMatrix);
	m_shader.Stop();
}

void EntityRenderer::RenderEntities(std::map<TexturedObject, std::vector<Entity>, TextureObjectCompare>& entities)
{
	// Loop through the mapObjects
	for (auto& mapObject : entities)
	{
		// key.first = TexturedModel, key.second = std::vector<Entity>
		// Bind the texturedModel's texture
		BindTexturedObject(mapObject.first);
		// Render all of the entities in the container
		for (auto& entity : mapObject.second)
			RenderEntity(entity);
		// Unbind the texturedModel
		UnbindTexturedModel();
	}
}

void EntityRenderer::EnableCulling()
{
	// Don't draw faces we can't see
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void EntityRenderer::DisableCulling()
{
	glDisable(GL_CULL_FACE);
}

void EntityRenderer::BindTexturedObject(TexturedObject texturedObject)
{
	// Get the BaseModel from the TexturedModel
	Object model = texturedObject.GetModelObject();
	// Bind the models vertex array object id so we can render it
	glBindVertexArray(model.GetVaoID());
	// Enable the attrib arrays 0 - Position, 1 - TextureCoords, 2 - Normals
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	// Load shineDamper and reflectivity from the texture
	Texture texture = texturedObject.GetModelTexture();
	// Activate an OpenGL texture unit and tell it where the texture is
	glActiveTexture(GL_TEXTURE0);
	// Bind the texturedModel's texture
	glBindTexture(GL_TEXTURE_2D, texturedObject.GetModelTexture().GetTextureID());
}

void EntityRenderer::UnbindTexturedModel()
{
	// Enable the cullface again
	EnableCulling();

	// Disable the attrib arrays
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void EntityRenderer::RenderEntity(Entity& entity)
{
	// Load the transformation matrix into the shader
	m_shader.LoadTransformationMatrix(Maths::CreateTransformationMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale()));

	// Draw the model
	glDrawElements(GL_TRIANGLES, entity.GetTexturedObject().GetModelObject().GetIndiceCount(), GL_UNSIGNED_INT, 0);
}
