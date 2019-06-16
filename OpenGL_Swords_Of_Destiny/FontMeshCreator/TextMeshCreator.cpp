#include "../pch.h"
#include "TextMeshCreator.hpp"


TextMeshCreator::TextMeshCreator(const std::string& metaFile)
	: _metaData(metaFile)
{

}

TextMeshData TextMeshCreator::CreateTextMesh(GUIText& text)
{
	std::vector<Line> lines = CreateStructure(text);
	TextMeshData data = CreateQuadVertices(text, lines);
	return data;
}

std::vector<Line> TextMeshCreator::CreateStructure(GUIText& text)
{
	auto chars = text.GetTextString().c_str();
	std::vector<Line> lines;
	Line currentLine(_metaData.GetSpaceWidth(), text.GetFontSize(), text.GetMaxLineSize());
	Word currentWord(text.GetFontSize());

	for (int i = 0; i < text.GetTextString().size(); i++)
	{
		int ascii = (int)chars[i];

		if (ascii == SPACE_ASCII)
		{
			bool added = currentLine.AttempToAddWord(currentWord);
			if (!added)
			{
				lines.push_back(currentLine);
				currentLine = Line(_metaData.GetSpaceWidth(), text.GetFontSize(), text.GetMaxLineSize());
				currentLine.AttempToAddWord(currentWord);
			}
			currentWord = Word(text.GetFontSize());
			continue;
		}
		Character character = _metaData.GetCharacter(ascii);
		currentWord.AddCharacter(character);
	}
	CompleteStructure(lines, currentLine, currentWord, text);
}

void TextMeshCreator::CompleteStructure(std::vector<Line>& lines, Line& currentLine, Word& currentWord, GUIText& text)
{
	bool added = currentLine.AttempToAddWord(currentWord);
	if (!added)
	{
		lines.push_back(currentLine);
		currentLine = Line(_metaData.GetSpaceWidth(), text.GetFontSize(), text.GetMaxLineSize());
		currentLine.AttempToAddWord(currentWord);
	}
	lines.push_back(currentLine);
}

TextMeshData TextMeshCreator::CreateQuadVertices(GUIText& text, std::vector<Line>& lines)
{
	text.SetNumberOfLines(lines.size());
	double curserX = 0.f;
	double curserY = 0.f;
	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> textureCoords;

	for (Line line : lines)
	{
		if (text.isCentered())
		{
			curserX = (line.GetMaxLength() - line.GetCurrentLineLength()) / 2;
		}
		for (Word word : line.GetWords())
		{
			for (Character letter : word.GetCharacters())
			{
				AddVerticesForCharacter(curserX, curserY, letter, text.GetFontSize(), vertices);
				AddTexCoords(textureCoords, letter.GetXTextureCoord(), letter.GetYTextureCoord(),
					letter.GetXMaxTextureCoord(), letter.GetYMaxTextureCoord());
				curserX += letter.GetXAdvance() * text.GetFontSize();
			}
			curserX += _metaData.GetSpaceWidth() * text.GetFontSize();
		}
		curserX = 0;
		curserY += LINE_HEIGHT * text.GetFontSize();
	}
	return TextMeshData(vertices, textureCoords);
}

void TextMeshCreator::AddVerticesForCharacter(double curserX, double curserY, Character character, double fontSize, std::vector<glm::vec2>& vertices)
{
	double x = curserX + (character.GetXOffset() * fontSize);
	double y = curserY + (character.GetYOffset() * fontSize);
	double maxX = x + (character.GetSizeX() * fontSize);
	double maxY = y + (character.GetSizeY() * fontSize);
	double properX = (2 * x) - 1;
	double properY = (-2 * y) + 1;
	double properMaxX = (2 * maxX) - 1;
	double properMaxY = (-2 * maxY) + 1;
	AddVertices(vertices, properX, properY, properMaxX, properMaxY);
}

void TextMeshCreator::AddVertices(std::vector<glm::vec2>& vertices, double x, double y, double maxX, double maxY)
{
	vertices.push_back(glm::vec2(x, y));
	vertices.push_back(glm::vec2(x, maxY));
	vertices.push_back(glm::vec2(maxX, maxY));
	vertices.push_back(glm::vec2(maxX, maxY));
	vertices.push_back(glm::vec2(maxX, y));
	vertices.push_back(glm::vec2(x, y));
}

void TextMeshCreator::AddTexCoords(std::vector<glm::vec2>& texCoords, double x, double y, double maxX, double maxY)
{
	texCoords.push_back(glm::vec2(x, y));
	texCoords.push_back(glm::vec2(x, maxY));
	texCoords.push_back(glm::vec2(maxX, maxY));
	texCoords.push_back(glm::vec2(maxX, maxY));
	texCoords.push_back(glm::vec2(maxX, y));
	texCoords.push_back(glm::vec2(x, y));
}
