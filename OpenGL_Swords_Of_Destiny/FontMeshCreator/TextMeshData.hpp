#ifndef TEXTMESHDATA_HPP
#define TEXTMESHDATA_HPP

class TextMeshData
{
public:
	// Constructor
	TextMeshData(std::vector<glm::vec2> vertexPositions, std::vector<glm::vec2> textureCoords);

	// Getters
	inline std::vector<glm::vec2>& GetVertexPositions() { return _vertexPositions; }
	inline std::vector<glm::vec2>& GetTextureCoords() { return _textureCoords; }
	inline int GetVertexCount() { return _vertexPositions.size(); }
private:
	std::vector<glm::vec2> _vertexPositions;
	std::vector<glm::vec2> _textureCoords;
};
#endif // !TEXTMESHDATA_HPP