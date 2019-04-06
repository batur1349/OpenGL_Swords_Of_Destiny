#include "../pch.h"
#include "MasterRenderer.hpp"


MasterRenderer::MasterRenderer(BasicShader & shader)
{
	CreateProjectionMatrix();

	shader.Start();
	shader.LoadProjectionMatrix(_projectionMatrix);
	shader.Stop();
}

MasterRenderer::~MasterRenderer()
{

}

void MasterRenderer::Prepare()
{
	// Enable the depth testing so 3d sceenes will be available
	glEnable(GL_DEPTH_TEST);

	// Clear the screen with this color
	glClearColor(0.4f, 0.3f, 0.4f, 0.5f);

	// Clear the previous frames buffered colors
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

const void MasterRenderer::Render(Entity & entity, BasicShader & shader) const
{
	// Get the model from entity
	Model model = entity.GetModel();

	// Get the base model from textured model
	BaseModel baseModel = model.GetBaseModel();

	// Bind the models vertex array object id so we can draw it
	glBindVertexArray(baseModel.GetVaoID());

	// Enable the position attribute
	glEnableVertexAttribArray(0);

	// Enable the texture coordinates attribute
	glEnableVertexAttribArray(1);

	// Enable the normal attribute
	glEnableVertexAttribArray(2);

	// Create the entities transformation matrix
	glm::mat4 transformationMatrix = Maths::CreateTransformationMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale());

	// Load the entities' transformation matrix to the gpu
	shader.LoadTransformationMatrix(transformationMatrix);

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

	// Disable the normal attribute
	glDisableVertexAttribArray(2);

	// Unbind the VAO
	glBindVertexArray(0);
}

void MasterRenderer::CreateProjectionMatrix()
{
	// Get the window parameters
	int width, height;
	glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);

	// Calculate the aspect ratio and frustum lenght
	float aspectRatio = (float)width / (float)height;
	float yScale = (1.0f / glm::tan(glm::radians(_FOV / 2.0f))) * aspectRatio;
	float xScale = yScale / aspectRatio;
	float frustumLenght = _FAR_PLANE - _NEAR_PLANE;

	// Set projectionmatrix to identity matrix
	_projectionMatrix = glm::mat4();

	// Calculate the perspective
	_projectionMatrix[0][0] = xScale;
	_projectionMatrix[1][1] = yScale;
	_projectionMatrix[2][2] = -((_FAR_PLANE + _NEAR_PLANE) / frustumLenght);
	_projectionMatrix[2][3] = -1;
	_projectionMatrix[3][2] = -((2 * _NEAR_PLANE * _FAR_PLANE) / frustumLenght);
	_projectionMatrix[3][3] = 0;
}
