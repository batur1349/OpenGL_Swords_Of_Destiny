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

void MasterRenderer::Render(TexturedObject& obj, ThirdPersonCamera& camera)
{
	// Start the shader
	m_shader.Start();

	// Load the shader matrices
	m_shader.LoadViewMatrix(camera);
	m_shader.LoadProjectionMatrix(m_projectionMatrix);
	glm::mat4 transformation;
	transformation = glm::scale(transformation, glm::vec3(0.5f));
	m_shader.LoadTransformationMatrix(transformation);

	// Bind the object vao
	glBindVertexArray(obj.GetModelObject().GetVaoID());
	// Enable the attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// Bind the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, obj.GetModelTexture().GetTextureID());

	// Draw the object
	glDrawElements(GL_TRIANGLES, obj.GetModelObject().GetIndiceCount(), GL_UNSIGNED_INT, 0);

	// Disable the attributes
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);

	m_shader.Stop();
}
