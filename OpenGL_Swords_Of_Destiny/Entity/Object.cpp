#include "../pch.h"
#include "Object.hpp"


Object::Object(GLuint& vaoID, int indiceCount)
{
	m_vaoID = vaoID;
	m_IndiceCount = indiceCount;
}
