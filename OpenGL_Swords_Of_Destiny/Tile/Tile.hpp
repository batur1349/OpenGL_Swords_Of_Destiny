#ifndef TILE_HPP
#define TILE_HPP

#include "../Entity/TexturedObject.hpp"
#include "../Loader/Loader.hpp"

class Tile
{
public:
	Tile(const TexturedObject& texObj, const glm::vec3& position, const glm::vec3& endPosition, std::pair<glm::vec3, glm::vec3> minmax);
	virtual ~Tile();

	// Getters
	inline TexturedObject& GetTexturedObject() { return m_texturedObject; }
	inline glm::vec3& GetPosition() { return m_position; }
	inline bool& GetSelected() { return m_selected; }
	inline float& GetStartX() { return m_position.x; }
	inline float& GetStartZ() { return m_position.z; }
	inline float& GetEndX() { return m_endPosition.x; }
	inline float& GetEndZ() { return m_endPosition.z; }
	inline glm::vec3& GetBounds(const int& index) { return bounds[index]; }

	// Setters
	void SetSelected(const bool& sel) { m_selected = sel; }
private:
	// Variables
	TexturedObject m_texturedObject;
	glm::vec3 m_position, m_endPosition;
	bool m_selected;
	glm::vec3 bounds[2];

	// Functions
	std::vector<glm::vec3> GenerateVertices();
	std::vector<glm::vec2> GenerateUvs();
	std::vector<glm::vec3> GenerateNormals();
	std::vector<int> GenerateIndices();
};

#endif // !TILE_HPP