#ifndef METAFILE_HPP
#define METAFILE_HPP

#include "Character.hpp"

constexpr float LINE_HEIGHT = 0.03f;
constexpr float SPACE_ASCII = 32.0f;

class MetaFile
{
public:
	// Constructor
	MetaFile(const std::string& file);

	// Getters
	inline double& GetSpaceWidth() { return _spaceWidth; }
	inline Character& GetCharacter(const int& ascii) { return _metaData.at(ascii); }
private:
	// Functions
	void OpenFile(const std::string& file);
	void LoadPaddingData();
	bool ProcessNextLine(); int _lineCounter = 0;
	std::vector<int> GetValuesOfVariable(const std::string& variable);
	void LoadLineSizes();
	int GetValueOfVariable(const std::string& variable);
	void LoadCharacterData(const int& imageWidth);
	Character LoadCharacter(const int& imageWidth);
	void Close();

	// Variables
	static const int PAD_TOP = 0, PAD_LEFT = 1, PAD_BOTTOM = 2, PAD_RIGHT = 3;
	static const int DESIRED_PADDING = 3;
	std::string SPLITTER = " ", NUMBER_SEPARATOR = ",", EQUAL_SEPERATOR = "=";
	double _aspectRatio, _verticalPerPixelSize, _horizontalPerPixelSize, _spaceWidth;
	std::vector<int> _padding;
	int _paddingWidth, _paddingHeight;

	std::ifstream _file;
	std::vector<std::string> _allLines;

	std::map<int, Character> _metaData;
	std::map<std::string, std::string> _values;
};

#endif // !METAFILE_HPP