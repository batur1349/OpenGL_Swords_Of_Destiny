#include "../pch.h"
#include "MasterRenderer.hpp"


MasterRenderer::MasterRenderer(float aspect, Loader& loader)
	: m_projectionMatrix(glm::perspective(m_FOV, aspect, m_NEAR_PLANE, m_FAR_PLANE))
{
	glEnable(GL_DEPTH_TEST);
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

void MasterRenderer::Render(Entity& entity, ThirdPersonCamera& camera)
{
	// Start the shader
	m_shader.Start();

	// Load the shader matrices
	m_shader.LoadViewMatrix(camera);
	m_shader.LoadProjectionMatrix(m_projectionMatrix);
	m_shader.LoadTransformationMatrix(Maths::CreateTransformationMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale()));

	// Bind the object vao
	glBindVertexArray(entity.GetTexturedModel().GetModelObject().GetVaoID());

	// Enable the attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// Bind the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, entity.GetTexturedModel().GetModelTexture().GetTextureID());

	// Draw the object
	glDrawElements(GL_TRIANGLES, entity.GetTexturedModel().GetModelObject().GetIndiceCount(), GL_UNSIGNED_INT, 0);

	// Disable the attributes
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	// Unbind the object vao
	glBindVertexArray(0);

	// Stop using the shader
	m_shader.Stop();
}
