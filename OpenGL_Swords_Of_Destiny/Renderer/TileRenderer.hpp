#ifndef TILERENDERER_HPP
#define TILERENDERER_HPP

#include "../Entity/TexturedObject.hpp"
#include "../Shader/TileShader.hpp"
#include "../Tile/Tile.hpp"
#include "../Maths/Maths.hpp"
#include "../Renderer/Frustum.hpp"

struct TileTextureObjectCompare
{
public:
	bool operator() (TexturedObject t1, TexturedObject t2) const
	{
		return ((t1.GetModelObject().GetVaoID() < t2.GetModelObject().GetVaoID()) ||
			(t1.GetModelTexture().GetTextureID() < t2.GetModelTexture().GetTextureID()));
	}
};

class TileRenderer
{
public:
	TileRenderer(TileShader& shader, const glm::mat4& projectionMatrix);

	// Functions
	void RenderTiles(std::map<TexturedObject, std::vector<Tile>, TileTextureObjectCompare>& tiles, Frustum& frustum);
	void EnableCulling();
	void DisableCulling();
private:
	// Functions
	void BindTexturedObject(TexturedObject texturedObject);
	void UnbindTexturedModel();
	void RenderTile(Tile& Tile);

	// Variables
	TileShader& m_shader;
};

#endif // !TILERENDERER_HPP