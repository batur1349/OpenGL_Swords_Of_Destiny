#include "../pch.h"
#include "Object.hpp"


Object::Object(GLuint& vaoID, int indiceCount, std::vector<glm::vec3> vertices)
{
	m_vaoID = vaoID;
	m_IndiceCount = indiceCount;
	m_vertices = vertices;
}
