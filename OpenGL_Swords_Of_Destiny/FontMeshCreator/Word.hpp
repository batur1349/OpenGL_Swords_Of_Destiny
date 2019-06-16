#ifndef WORD_HPP
#define WORD_HPP

#include "Character.hpp"

class Word
{
public:
	// Constructor
	Word(const double& fontSize);

	// Functions
	void AddCharacter(Character character);

	// Getters
	inline std::vector<Character>& GetCharacters() { return _characters; }
	inline double& GetWordWidth() { return _width; }
private:
	std::vector<Character> _characters;
	double _width = 0;
	double _fontSize;
};

#endif // !WORD_HPP