#include "../pch.h"
#include "MasterRenderer.hpp"


MasterRenderer::MasterRenderer()
{

}

MasterRenderer::~MasterRenderer()
{

}

void MasterRenderer::Prepare()
{
	// Clear the screen with this color
	glClearColor(0.4f, 0.3f, 0.4f, 0.5f);

	// Clear the previous frames buffered colors
	glClear(GL_COLOR_BUFFER_BIT);
}

const void MasterRenderer::Render(BaseModel & model) const
{
	// Bind the models vertex array object id so we can draw it
	glBindVertexArray(model.GetVaoID());

	// Enable the position attribute
	glEnableVertexAttribArray(0);

	// Draw the model
	glDrawElements(GL_TRIANGLES, model.GetVertexCount(), GL_UNSIGNED_INT, 0);

	// Disable the position attribute
	glDisableVertexAttribArray(0);

	// Unbind the VAO
	glBindVertexArray(0);
}

const void MasterRenderer::Render(Model & model) const
{
	// Get the base model from textured model
	BaseModel baseModel = model.GetBaseModel();

	// Bind the models vertex array object id so we can draw it
	glBindVertexArray(baseModel.GetVaoID());

	// Enable the position attribute
	glEnableVertexAttribArray(0);

	// Enable the texture coordinates attribute
	glEnableVertexAttribArray(1);

	// Activate the texture unit
	glActiveTexture(GL_TEXTURE0);

	// Get the texture from textured model
	Texture texture = model.GetTexture();

	// Bind the textured models texture
	glBindTexture(GL_TEXTURE_2D, texture.GetTextureID());

	// Draw the model
	glDrawElements(GL_TRIANGLES, baseModel.GetVertexCount(), GL_UNSIGNED_INT, 0);

	// Disable the position attribute
	glDisableVertexAttribArray(0);

	// Disable the texture coordinates attribute
	glDisableVertexAttribArray(1);

	// Unbind the VAO
	glBindVertexArray(0);
}
