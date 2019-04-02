#ifndef TEXTURE_HPP
#define TEXTURE_HPP

class Texture
{
public:
	// Contructor 
	Texture(GLuint id);

	// Getters
	const GLuint& GetTextureID() const;
private:
	// Variables
	GLuint _textureID;
};
#endif // !TEXTURE_HPP