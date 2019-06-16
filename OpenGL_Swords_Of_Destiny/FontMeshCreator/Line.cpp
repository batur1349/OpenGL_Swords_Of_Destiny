#include "../pch.h"
#include "Line.hpp"


Line::Line(double spaceWidth, double fontSize, double maxLength)
{
	_spaceSize = spaceWidth * fontSize;
	_maxLength = maxLength;
}

bool Line::AttempToAddWord(Word word)
{
	double additionalLength = word.GetWordWidth();
	additionalLength += !_words.empty() ? _spaceSize : 0;

	if (_currentLineLength + additionalLength <= _maxLength)
	{
		_words.push_back(word);
		_currentLineLength += additionalLength;
	}
	else
	{
		return false;
	}
}
