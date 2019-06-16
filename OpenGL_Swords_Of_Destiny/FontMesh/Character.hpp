//#ifndef CHARACTER_HPP
//#define CHARACTER_HPP
#pragma once
class Character
{
public:
	// Constructor
	Character(int id, double xTextureCoord, double yTextureCoord, double xTexSize, double yTexSize,
		double xOffset, double yOffset, double sizeX, double sizeY, double xAdvance);

	// Getters
	inline GLuint& GetTextureId() { return _textureId; }
	inline double& GetXTextureCoord() { return _xTextureCoord; }
	inline double& GetYTextureCoord() { return _yTextureCoord; }
	inline double& GetXMaxTextureCoord() { return _xMaxTextureCoord; }
	inline double& GetYMaxTextureCoord() { return _yMaxTextureCoord; }
	inline double& GetXOffset() { return _xOffset; }
	inline double& GetYOffset() { return _yOffset; }
	inline double& GetSizeX() { return _sizeX; }
	inline double& GetSizeY() { return _sizeY; }
	inline double& GetXAdvance() { return _xAdvance; }
private:
	GLuint _textureId;
	double _xTextureCoord, _yTextureCoord;
	double _xMaxTextureCoord, _yMaxTextureCoord;
	double _xOffset, _yOffset;
	double _sizeX, _sizeY;
	double _xAdvance;
};
//#endif // !CHARACTER_HPP