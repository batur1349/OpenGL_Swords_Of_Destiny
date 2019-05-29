#ifndef LOADER_HPP
#define LOADER_HPP

#include "../Entity/Object.hpp"

class Loader
{
public:
	// Constructor
	Loader();
	~Loader();
	// Functions
	Object LoadToVAO(std::vector<glm::vec3> vertices, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals, std::vector<int> indices);
	Object LoadAssimpObjFile(const std::string& fileName);
private:
	// Variables
	std::vector<GLuint> m_vaos;
	std::vector<GLuint> m_vbos;

	// Functions
	GLuint CreateVaoID();
	void LoadIndicesToGPU(int indices[], int& count);
	void LoadDataToAttributeList(GLuint attribNumber, int attribSize, void* data, int dataSize);
	inline void UnbindVAO() { glBindVertexArray(0); }
};

#endif // !LOADER_HPP