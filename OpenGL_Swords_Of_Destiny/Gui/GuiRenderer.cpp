#include "../pch.h"
#include "GuiRenderer.hpp"


GuiRenderer::GuiRenderer(Loader& loader)
	: _object(ConstructObject(loader))
{
}

GuiRenderer::~GuiRenderer()
{
}

void GuiRenderer::Render(std::vector<GuiTexture>& guis)
{
	_shader.Start();
	glBindVertexArray(_object.GetVaoID());
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	for (int i = 0; i < guis.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, guis.at(i).GetTextureID());
		glm::mat4 matrix = Maths::CreateGuiTransformationMatrix(guis.at(i).GetPosition(), guis.at(i).GetScale());
		_shader.LoadTransformationMatrix(matrix);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, _object.GetIndiceCount());
	}

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	_shader.Stop();
}

Object GuiRenderer::ConstructObject(Loader& loader)
{
	std::vector<glm::vec2> positions;
	positions.emplace_back(-1, 1);
	positions.emplace_back(-1, -1);
	positions.emplace_back(1, 1);
	positions.emplace_back(1, -1);

	return Object(loader.LoadToVAO(positions));
}
