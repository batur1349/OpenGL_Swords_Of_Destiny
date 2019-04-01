#include "../pch.h"
#include "BaseModel.hpp"


BaseModel::BaseModel(GLuint & vaoID, int vertexCount)
{
	_vaoID = vaoID;
	_vertexCount = vertexCount;
}

void BaseModel::Render()
{
	if (_vaoID)
	{
		// Bind the models vertex array object id so we can draw it
		glBindVertexArray(_vaoID);
		// Enable the position attribute
		glEnableVertexAttribArray(0);
		// Draw the model
		glDrawElements(GL_TRIANGLES, _vertexCount, GL_UNSIGNED_INT, 0);
		// Disable the position attribute
		glDisableVertexAttribArray(0);
		// Unbind the VAO
		glBindVertexArray(0);
	}
}
