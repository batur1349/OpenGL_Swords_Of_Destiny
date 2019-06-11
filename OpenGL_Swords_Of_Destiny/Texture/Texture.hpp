#ifndef TEXTURE_HPP
#define TEXTURE_HPP

class Texture
{
public:
	// Contructor 
	Texture() { m_textureID = 9999999; }
	Texture(GLuint id);

	// Getters
	inline GLuint& GetTextureID() { return m_textureID; }
	inline float& GetShinedamper() { return m_shineDamper; }
	inline float& GetReflectivity() { return m_reflectivity; }
	inline bool& GetFakeLightning() { return m_fakeLightning; }
	inline bool& GetTransparency() { return m_transparency; }

	// Setter
	void SetShinedamper(const float& damper) { m_shineDamper = damper; }
	void SetReflectivity(const float& ref) { m_reflectivity = ref; }
	void SetFakeLightning(const bool& fklight) { m_fakeLightning = fklight; }
	void SetTransparency(const bool& trans) { m_transparency = trans; }
private:
	// Variables
	GLuint m_textureID;
	float m_shineDamper = 1.0f;
	float m_reflectivity = 0.0f;
	bool m_fakeLightning = false, m_transparency = false;
};
#endif // !TEXTURE_HPP