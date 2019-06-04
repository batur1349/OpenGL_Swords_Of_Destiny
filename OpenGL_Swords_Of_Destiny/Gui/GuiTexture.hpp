#ifndef GUITEXTURE_HPP
#define GUITEXTURE_HPP

class GuiTexture
{
public:
	// Constructor
	GuiTexture(GLuint texture, glm::vec2 position, glm::vec2 scale);

	// Getters
	inline GLuint GetTextureID() { return _texture; }
	inline glm::vec2 GetPosition() { return _position; }
	inline glm::vec2 GetScale() { return _scale; }
private:
	// Variables
	GLuint _texture;
	glm::vec2 _position, _scale;
};

#endif // !GUITEXTURE_HPP