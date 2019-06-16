#ifndef TEXTMESHCREATOR_HPP
#define TEXTMESHCREATOR_HPP

#include "MetaFile.hpp"
#include "TextMeshData.hpp"
#include "GUIText.hpp"
class GUIText;
#include "Line.hpp"

constexpr float TMC_LINE_HEIGHT = 0.03f;
constexpr float TMC_SPACE_ASCII = 32.0f;

class TextMeshCreator
{
public:
	// Constructor
	TextMeshCreator(const std::string& metaFile);

	// Functions
	TextMeshData CreateTextMesh(GUIText& text);
private:
	// Functions
	std::vector<Line> CreateStructure(GUIText& text);
	void CompleteStructure(std::vector<Line>& lines, Line& currentLine, Word& currentWord, GUIText& text);
	TextMeshData CreateQuadVertices(GUIText& text, std::vector<Line>& lines);
	void AddVerticesForCharacter(double curserX, double curserY, Character character, double fontSize, std::vector<glm::vec2>& vertices);
	void AddVertices(std::vector<glm::vec2>& vertices, double x, double y, double maxX, double maxY);
	void AddTexCoords(std::vector<glm::vec2>& texCoords, double x, double y, double maxX, double maxY);

	// Variables
	MetaFile _metaData;
};

#endif // !TEXTMESHCREATOR_HPP