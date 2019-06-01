#ifndef TILE_HPP
#define TILE_HPP

#include "../../Entity/TexturedObject.hpp"
#include "../../Loader/Loader.hpp"

constexpr int VERTEX_COUNT = 256;
constexpr int SIZE_OF_TILE = 800;

class Tile
{
public:
	Tile(int gridX, int gridZ, Loader& loader, const std::string& textureName);
	Tile(int gridX, int gridZ, int sizeoftile, int vertexcount, Loader& loader, const std::string& textureName);

	// Getters
	inline Object& GetBaseModel() { return _model; }
	inline float& GetX() { return _x; }
	inline float& GetZ() { return _z; }
	inline float& GetStartX() { return _startX; }
	inline float& GetStartZ() { return _startZ; }
	inline float& GetEndX() { return _endX; }
	inline float& GetEndZ() { return _endZ; }
	inline GLuint& GetTextureID() { return _texture.GetTextureID(); }
private:
	// Variables
	std::vector<std::vector<float>> _heights;
	float _x, _z, _startX, _startZ, _endX, _endZ;
	int _sizeOfTile, _vertexCount;

	Object _model;
	Texture _texture;

	// Functions
	Object GenerateTile(Loader& loader);
};

#endif // !TILE_HPP