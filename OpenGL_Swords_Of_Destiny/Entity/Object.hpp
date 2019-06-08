#ifndef OBJECT_HPP
#define OBJECT_HPP

class Object
{
public:
	// Constructor
	Object(GLuint& vaoID, int indiceCount, std::vector<glm::vec3> vertices);

	// Getters
	inline GLuint& GetVaoID() { return m_vaoID; }
	inline int& GetIndiceCount() { return m_IndiceCount; }
private:
	GLuint m_vaoID;
	int m_IndiceCount;
	std::vector<glm::vec3> m_vertices;
};

#endif // !OBJECT_HPP