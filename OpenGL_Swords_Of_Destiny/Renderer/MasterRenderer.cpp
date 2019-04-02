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
