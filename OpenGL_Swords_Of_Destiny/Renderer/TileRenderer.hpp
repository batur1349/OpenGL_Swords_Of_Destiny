#ifndef TILERENDERER_HPP
#define TILERENDERER_HPP

#include "../Shader/TileShader.hpp"
#include "../TileMap/Tile/Tile.hpp"

class TileRenderer
{
public:
	// Constructor and ~Destructor
	TileRenderer(TileShader& shader, const glm::mat4& projectionMatrix);

	// Functions
	void Render(std::vector<Tile>& tiles);
private:
	// Functions
	void PrepareTile(Tile& tile);
	void UnbindTexturedModel();
	void LoadModelMatrix(Tile& tile);
	void BindTextures(Tile& tile);

	// Variables
	TileShader& m_shader;
};

#endif // !TILERENDERER_HPP
