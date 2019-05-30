#include "../pch.h"
#include "MasterRenderer.hpp"


MasterRenderer::MasterRenderer(float aspect, Loader& loader)
	: m_projectionMatrix(glm::perspective(m_FOV, aspect, m_NEAR_PLANE, m_FAR_PLANE))
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

void MasterRenderer::Render(std::vector<Entity>& entities, ThirdPersonCamera& camera)
{
	// Start the shader
	m_shader.Start();

	// Load the shader matrices
	m_shader.LoadViewMatrix(camera);
	m_shader.LoadProjectionMatrix(m_projectionMatrix);

	// Bind the object vao
	glBindVertexArray(entities.at(0).GetTexturedModel().GetModelObject().GetVaoID());

	// Enable the attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// Bind the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, entities.at(0).GetTexturedModel().GetModelTexture().GetTextureID());

	// Draw the object
	for (int i = 0; i < entities.size(); i++)
	{
		m_shader.LoadTransformationMatrix(Maths::CreateTransformationMatrix(entities.at(i).GetPosition(),
			entities.at(i).GetRotation(), entities.at(i).GetScale()));
		glDrawElements(GL_TRIANGLES, entities.at(i).GetTexturedModel().GetModelObject().GetIndiceCount(), GL_UNSIGNED_INT, 0);
	}

	// Disable the attributes
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	// Unbind the object vao
	glBindVertexArray(0);

	// Stop using the shader
	m_shader.Stop();
}
