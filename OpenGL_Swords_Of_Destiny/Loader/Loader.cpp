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
	for (int i = 0; i < _textures.size(); i++)
		glDeleteBuffers(1, &_textures.at(i));
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

BaseModel Loader::LoadToVAO(std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& textures, std::vector<int>& indices)
{
	// Create the vertex array object's id
	GLuint vaoID = CreateObjectVaoID();

	// Send indices data to the GPU
	int indicesSize = indices.size();
	LoadIndicesToGPU(indices.data(), indicesSize);

	// Load positions data to the attribute list 0
	LoadDataToAttributeList(0, 3, vertices.data(), sizeof(glm::vec3) * vertices.size());

	// Load the texture coordinates data to the attribute list 1
	LoadDataToAttributeList(1, 2, textures.data(), sizeof(glm::vec2) * textures.size());
	// Unbind the vertex array object
	UnbindVAO();
	// Return the raw model
	return BaseModel(vaoID, indicesSize);
}

GLuint Loader::LoadTexture2D(const std::string & fileName)
{
	// Create a texture id
	GLuint texture;

	// Create the temporal variables
	int width, height;

	// Generate the texture
	glGenTextures(1, &texture);

	// Load the image data
	unsigned char* image;
	image = SOIL_load_image(("../Textures/" + fileName + ".png").c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

	// Bind the texture data
	glBindTexture(GL_TEXTURE_2D, texture);

	// Texture the loaded 2D image data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	// Generate the mipmap texture
	glGenerateMipmap(GL_TEXTURE_2D);

	// Add the image to the textures container
	_textures.push_back(texture);

	// Clean-up the image data
	SOIL_free_image_data(image);

	// Texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// Return the texture id
	return texture;
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
