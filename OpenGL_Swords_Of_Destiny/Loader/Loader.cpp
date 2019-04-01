#include "../pch.h"
#include "Loader.hpp"


Loader::Loader()
{

}

Loader::~Loader()
{
	for (int i = 0; i < _vaos.size(); i++)
		glDeleteVertexArrays(1, &_vaos.at(i));
	for (int i = 0; i < _vbos.size(); i++)
		glDeleteBuffers(1, &_vbos.at(i));
}

BaseModel Loader::LoadToVAO(std::vector<glm::vec3> vertices, std::vector<int> indices, int positionsCount, int indicesCount)
{
	// Create the vertex array object's id
	GLuint vaoID = CreateObjectVaoID();
	// Send indices data to the GPU
	LoadIndicesToGPU(indices.data(), indicesCount);
	// Load positions data to the attribute list 0
	LoadDataToAttributeList(0, 3, vertices.data(), sizeof(glm::vec3) * vertices.size());
	// Unbind the vertex array object
	UnbindVAO();
	// Return the raw model
	return BaseModel(vaoID, indicesCount);
}

GLuint Loader::CreateObjectVaoID()
{
	GLuint vaoID;
	// Generate vertex array object
	glGenVertexArrays(1, &vaoID);
	// Add vertex array object to the container
	_vaos.push_back(vaoID);
	// Bind the vertex array object
	glBindVertexArray(vaoID);
	// Return the vertex array object
	return vaoID;
}

void Loader::LoadIndicesToGPU(int indices[], int & count)
{
	GLuint vboID;
	// Generate the vertex buffer object
	glGenBuffers(1, &vboID);
	// Add vertex buffer object to the container
	_vbos.push_back(vboID);
	// Bind the vertex buffer object to the element array buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	// Send the element object with vertex buffer object
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * count, indices, GL_STATIC_DRAW);
}

void Loader::LoadDataToAttributeList(GLuint attribNumber, int attribSize, void * data, int dataSize)
{
	GLuint vboID;
	// Create a new vertex buffer object
	glGenBuffers(1, &vboID);
	// Add vertex buffer object to the container
	_vbos.push_back(vboID);
	// Bind the vertex buffer object to use it
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	// Load the data to GPU using the vertex buffer object
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	// Tell OpenGL how and where to store this VBO in the VAO
	glVertexAttribPointer(attribNumber, attribSize, GL_FLOAT, GL_FALSE, 0, nullptr);
	// Unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
