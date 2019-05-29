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

void MasterRenderer::Render(Object& object, ThirdPersonCamera& camera)
{
	// Start the shader
	m_shader.Start();

	m_shader.LoadViewMatrix(camera);
	m_shader.LoadProjectionMatrix(m_projectionMatrix);
	glm::mat4 transformation;
	transformation = glm::scale(transformation, glm::vec3(0.5f));
	m_shader.LoadTransformationMatrix(transformation);

	glBindVertexArray(object.GetVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 1);

	//glEnableVertexAttribArray(2);
	glDrawElements(GL_TRIANGLES, object.GetIndiceCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(2);
	glBindVertexArray(0);

	m_shader.Stop();
}
