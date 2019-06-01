#include "../../pch.h"
#include "Tile.hpp"


Tile::Tile(int gridX, int gridZ, Loader& loader, const std::string& textureName)
	: _sizeOfTile(SIZE_OF_TILE), _vertexCount(VERTEX_COUNT), _model(GenerateTile(loader)), _texture(loader.LoadTexture2D(textureName))
{
	_x = gridX * _sizeOfTile;
	_z = gridZ * _sizeOfTile;

	_startX = _x;
	_startZ = _z;

	_endX = _startX + _sizeOfTile;
	_endZ = _startZ + _sizeOfTile;
}

Tile::Tile(int gridX, int gridZ, int sizeoftile, int vertexcount, Loader& loader, const std::string& textureName)
	: _sizeOfTile(sizeoftile), _vertexCount(vertexcount), _model(GenerateTile(loader)), _texture(loader.LoadTexture2D(textureName))
{
	_x = gridX * _sizeOfTile;
	_z = gridZ * _sizeOfTile;

	_startX = _x;
	_startZ = _z;

	_endX = _startX + _sizeOfTile;
	_endZ = _startZ + _sizeOfTile;
}

Object Tile::GenerateTile(Loader& loader)
{
	std::cout << "Staring to generating of Terrain" << std::endl;
	clock_t startTime = clock();

	int count = _vertexCount * _vertexCount;

	std::vector<glm::vec3> vertices(count), normals(count);
	std::vector<glm::vec2> textureCoords(count);
	std::vector<int> indices(6 * (_vertexCount - 1) * _vertexCount);

	_heights = std::vector<std::vector<float>>(_vertexCount, std::vector<float>(_vertexCount));

	int vertexPointer = 0;
	for (int i = 0; i < _vertexCount; i++)
	{
		for (int j = 0; j < _vertexCount; j++)
		{
			float height = 0.0f;
			_heights.at(j).at(i) = height;

			vertices[vertexPointer] = glm::vec3(
				(float)j / ((float)_vertexCount - 1) * _sizeOfTile,
				height,
				(float)i / ((float)_vertexCount - 1) * _sizeOfTile);

			normals[vertexPointer] = glm::vec3(0.0f, 1.0f, 0.0f);

			textureCoords[vertexPointer] = glm::vec2(
				(float)j / ((float)_vertexCount - 1),
				(float)i / ((float)_vertexCount - 1));

			vertexPointer++;
		}
	}

	int pointer = 0;
	for (int gz = 0; gz < _vertexCount - 1; gz++)
	{
		for (int gx = 0; gx < _vertexCount - 1; gx++)
		{
			int topLeft = (gz * _vertexCount) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * _vertexCount) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}

	// Print the time
	std::printf("Load time: %dms\n", clock() - startTime);

	return loader.LoadToVAO(vertices, textureCoords, normals, indices);
}
