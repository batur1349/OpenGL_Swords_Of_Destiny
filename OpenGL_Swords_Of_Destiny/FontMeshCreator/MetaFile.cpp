#include "../pch.h"
#include "MetaFile.hpp"


MetaFile::MetaFile(const std::string& file)
{
	int width, height;
	glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
	_aspectRatio = (float)width / (float)height;

	OpenFile(file);
	LoadPaddingData();
	LoadLineSizes();
	int imageWidth = GetValueOfVariable("scaleW");
	LoadCharacterData(imageWidth);
}

void MetaFile::OpenFile(const std::string& file)
{
	_file.open(file);
	_allLines.clear();

	std::string line;
	if (_file.is_open())
	{
		while (std::getline(_file, line))
		{
			_allLines.push_back(line);
		}
	}
	else
	{
		std::cout << "Error, while openning the file \n";
		exit(1);
	}
}

void MetaFile::LoadPaddingData()
{
	ProcessNextLine();
	_padding = GetValuesOfVariable("padding");
	_paddingWidth = _padding[PAD_LEFT] + _padding[PAD_RIGHT];
	_paddingHeight = _padding[PAD_TOP] + _padding[PAD_BOTTOM];
}

bool MetaFile::ProcessNextLine()
{
	_values.clear();
	std::string line, oldToken = "";
	line = _allLines.at(_lineCounter);

	if (line == "")
	{
		return false;
	}
	else
	{
		while (line != "")
		{
			std::string token = line.substr(0, line.find(SPLITTER));
			if (oldToken == token) break;
			if (token != "")
			{
				std::string pair1 = token.substr(0, token.find("="));
				oldToken = token;
				line.erase(0, line.find(SPLITTER) + SPLITTER.length());
				token.erase(0, token.find("=") + EQUAL_SEPERATOR.length());
				std::string pair2 = token;

				if (pair1 != pair2)
				{
					_values.insert(std::make_pair(pair1, pair2));
				}
			}
			else
			{
				line.erase(line.begin());
			}
		}
	}

	_lineCounter++;
}

std::vector<int> MetaFile::GetValuesOfVariable(const std::string& variable)
{
	std::string numbers = _values.at(variable);
	std::string pad1 = numbers.substr(0, numbers.find(NUMBER_SEPARATOR));
	numbers.erase(0, numbers.find(",") + NUMBER_SEPARATOR.length());
	std::string pad2 = numbers.substr(0, numbers.find(NUMBER_SEPARATOR));
	numbers.erase(0, numbers.find(",") + NUMBER_SEPARATOR.length());
	std::string pad3 = numbers.substr(0, numbers.find(NUMBER_SEPARATOR));
	numbers.erase(0, numbers.find(",") + NUMBER_SEPARATOR.length());
	std::string pad4 = numbers.substr(0, numbers.find(NUMBER_SEPARATOR));

	std::vector<int> actualValues;
	actualValues.push_back(std::stoi(pad1));
	actualValues.push_back(std::stoi(pad2));
	actualValues.push_back(std::stoi(pad3));
	actualValues.push_back(std::stoi(pad4));

	return actualValues;
}

void MetaFile::LoadLineSizes()
{
	ProcessNextLine();
	int lineHeightPixels = GetValueOfVariable("lineHeight") - _paddingHeight;
	_verticalPerPixelSize = LINE_HEIGHT / (double)lineHeightPixels;
	_horizontalPerPixelSize = _verticalPerPixelSize / _aspectRatio;
}

int MetaFile::GetValueOfVariable(const std::string& variable)
{
	return std::stoi(_values.at(variable));
}

void MetaFile::LoadCharacterData(const int& imageWidth)
{
	ProcessNextLine();
	ProcessNextLine();

	while (ProcessNextLine()) {
		Character c = LoadCharacter(imageWidth);
		_metaData.insert(std::make_pair(c.GetTextureId(), c));
	}
}

Character MetaFile::LoadCharacter(const int& imageWidth)
{
	int id = GetValueOfVariable("id");
	/*if (id == SPACE_ASCII)
	{
		_spaceWidth = (GetValueOfVariable("xadvance") - _paddingWidth) * _horizontalPerPixelSize;
	}*/
	double xTex = ((double)GetValueOfVariable("x") + (_padding[PAD_LEFT] - DESIRED_PADDING)) / imageWidth;
	double yTex = ((double)GetValueOfVariable("y") + (_padding[PAD_TOP] - DESIRED_PADDING)) / imageWidth;
	int width = GetValueOfVariable("width") - (_paddingWidth - (2 * DESIRED_PADDING));
	int height = GetValueOfVariable("height") - ((_paddingHeight)-(2 * DESIRED_PADDING));
	double quadWidth = width * _horizontalPerPixelSize;
	double quadHeight = height * _verticalPerPixelSize;
	double xTexSize = (double)width / imageWidth;
	double yTexSize = (double)height / imageWidth;
	double xOff = (GetValueOfVariable("xoffset") + _padding[PAD_LEFT] - DESIRED_PADDING) * _horizontalPerPixelSize;
	double yOff = (GetValueOfVariable("yoffset") + (_padding[PAD_TOP] - DESIRED_PADDING)) * _verticalPerPixelSize;
	double xAdvance = (GetValueOfVariable("xadvance") - _paddingWidth) * _horizontalPerPixelSize;
	return Character(id, xTex, yTex, xTexSize, yTexSize, xOff, yOff, quadWidth, quadHeight, xAdvance);
}

void MetaFile::Close()
{
	_file.close();
}
