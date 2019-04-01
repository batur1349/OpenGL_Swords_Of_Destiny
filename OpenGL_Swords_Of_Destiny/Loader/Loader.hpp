#ifndef LOADER_HPP
#define LOADER_HPP

#include "../Model/BaseModel.hpp"
class BaseModel;

class Loader
{
public:
	// Constructor and ~Destructor
	Loader();
	~Loader();

	// Functions
	BaseModel LoadToVAO(std::vector<glm::vec3> vertices, std::vector<int> indices, int positionsCount, int indicesCount);
private:
	// Variables
	std::vector<GLuint> _vaos;
	std::vector<GLuint> _vbos;

	// Functions
	GLuint CreateObjectVaoID();
	void LoadIndicesToGPU(int indices[], int& count);
	void LoadDataToAttributeList(GLuint attribNumber, int attribSize, void* data, int dataSize);
	const inline void UnbindVAO() const { glBindVertexArray(0); }
};

#endif // !LOADER_HPP