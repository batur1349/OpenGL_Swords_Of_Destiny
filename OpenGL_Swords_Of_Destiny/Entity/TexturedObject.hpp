#ifndef TEXTUREDOBJECT_HPP
#define TEXTUREDOBJECT_HPP

#include "Object.hpp"
#include "../Texture/Texture.hpp"

class TexturedObject
{
public:
	// Constructor
	TexturedObject(Object obj, Texture text);

	// Getters
	inline Object& GetModelObject() { return m_object; }
	inline Texture& GetModelTexture() { return m_texture; }

	// Setters
	void SetObject(Object& obj) { m_object = obj; }
private:
	Object m_object;
	Texture m_texture;
};

#endif // !TEXTUREDOBJECT_HPP