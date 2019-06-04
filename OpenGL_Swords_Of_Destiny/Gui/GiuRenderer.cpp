#include "../pch.h"
#include "GuiRenderer.hpp"


GuiRenderer::GuiRenderer(Loader& loader)
{
	_baseModel = new BaseModel(loader.LoadToVAO(positions));
}

GuiRenderer::~GuiRenderer()
{
	delete _baseModel;
}

void GuiRenderer::Render(std::vector<GuiTexture> guis)
{
	_shader.Start();
	glBindVertexArray(_baseModel->GetVaoID());
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	for (int i = 0; i < guis.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, guis.at(i).GetTextureID());
		glm::mat4 matrix = Maths::CreateTransformationMatrix(guis.at(i).GetPosition(), guis.at(i).GetScale());
		_shader.LoadTransformationMatrix(matrix);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, _baseModel->GetVertexCount());
	}

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	_shader.Stop();
}
