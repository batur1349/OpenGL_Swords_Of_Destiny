#ifndef LINE_HPP
#define LINE_HPP

#include "Word.hpp"

class Line
{
public:
	// Constructor
	Line(double spaceWidth, double fontSize, double maxLength);

	// Functions
	bool AttempToAddWord(Word word);

	// Getters
	inline double& GetMaxLength() { return _maxLength; }
	inline double& GetCurrentLineLength() { return _currentLineLength; }
	inline std::vector<Word>& GetWords() { return _words; }
private:
	double _maxLength, _spaceSize;
	double _currentLineLength = 0;
	std::vector<Word> _words;
};

#endif // !LINE_HPP