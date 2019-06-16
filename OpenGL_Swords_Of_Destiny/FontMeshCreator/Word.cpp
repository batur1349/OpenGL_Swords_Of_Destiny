#include "../pch.h"
#include "Word.hpp"


Word::Word(const double& fontSize)
{
	_fontSize = fontSize;
}

void Word::AddCharacter(Character character)
{
	_characters.push_back(character);
	_width += character.GetXAdvance() * _fontSize;
}
