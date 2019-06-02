#ifndef TILE_HPP
#define TILE_HPP

#include "../Entity/TexturedObject.hpp"
#include "../Loader/Loader.hpp"

class Tile
{
public:
	Tile(const TexturedObject& texObj, const glm::vec3& position);
	Tile(const std::string& texName, const glm::vec3& position, Loader& loader);
	virtual ~Tile();

	// Getters
	inline TexturedObject& GetTexturedObject() { return m_texturedObject; }
	inline glm::vec3& GetPosition() { return m_position; }
	inline bool& GetSelected() { return m_selected; }

	// Setters
	void SetSelected(const bool& sel) { m_selected = sel; }
private:
	// Variables
	TexturedObject m_texturedObject;
	glm::vec3 m_position;
	bool m_selected;

	// Functions
	std::vector<glm::vec3> GenerateVertices();
	std::vector<glm::vec2> GenerateUvs();
	std::vector<glm::vec3> GenerateNormals();
	std::vector<int> GenerateIndices();
};

#endif // !TILE_HPP