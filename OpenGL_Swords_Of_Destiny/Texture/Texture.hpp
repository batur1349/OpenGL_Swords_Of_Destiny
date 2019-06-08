#ifndef TEXTURE_HPP
#define TEXTURE_HPP

class Texture
{
public:
	// Contructor 
	Texture() { m_textureID = 9999999; }
	Texture(GLuint id);
	// Getters
	GLuint& GetTextureID();
private:
	// Variables
	GLuint m_textureID;
};
#endif // !TEXTURE_HPP