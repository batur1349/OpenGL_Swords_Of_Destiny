#include "../pch.h"
#include "Loader.hpp"


Loader::Loader()
{
	// Initialize the containers
	m_vaos.clear();
	m_vbos.clear();
	m_textures.clear();
}

Loader::~Loader()
{
	for (int i = 0; i < m_vaos.size(); i++)
		glDeleteVertexArrays(1, &m_vaos.at(i));

	for (int i = 0; i < m_vbos.size(); i++)
		glDeleteBuffers(1, &m_vbos.at(i));

	for (int i = 0; i < m_textures.size(); i++)
		glDeleteTextures(1, &m_textures.at(i));
}

Object Loader::LoadToVAO(std::vector<glm::vec2>& vertices)
{
	// Create the vertex array object's id
	GLuint vaoID = CreateVaoID();
	// Load positions data to the attribute list 0
	LoadDataToAttributeList(0, 2, vertices.data(), sizeof(glm::vec2) * vertices.size());
	// Unbind the vertex array object
	UnbindVAO();
	// Return the raw model
	return Object(vaoID, vertices.size());
}

Object Loader::LoadToVAO(std::vector<glm::vec3> vertices, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals, std::vector<int> indices)
{
	// Create the vertex array object's id
	GLuint vaoID = CreateVaoID();

	// Send indices data to the GPU
	int indicesSize = indices.size();
	LoadIndicesToGPU(indices.data(), indicesSize);

	// Load positions data to the attribute list 0
	LoadDataToAttributeList(0, 3, vertices.data(), sizeof(glm::vec3) * vertices.size());

	// Load the texture coordinates data to the attribute list 1
	LoadDataToAttributeList(1, 2, textures.data(), sizeof(glm::vec2) * textures.size());

	// Load the normal coordinates data to the attribute list 2
	LoadDataToAttributeList(2, 3, normals.data(), sizeof(glm::vec3) * normals.size());

	// Unbind the vertex array object
	UnbindVAO();

	// Return the raw model
	return Object(vaoID, indicesSize);
}

Object Loader::LoadAssimpObjFile(const std::string& fileName)
{
	std::cout << "Loading OBJ file " << fileName << ".obj ..." << "\n";
	// Start timer
	clock_t startTime = clock();

	// Actual importer
	Assimp::Importer importer;

	// Static containers
	std::vector<int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	// Actual path
	std::string path = "../Objects/" + fileName + ".obj";

	const aiScene* scene = importer.ReadFile(path, aiProcess_JoinIdenticalVertices | aiProcess_SortByPType | aiProcess_ConvertToLeftHanded);
	if (!scene)
	{
		fprintf(stderr, importer.GetErrorString());
		getchar();
	}

	const aiMesh* mesh = scene->mMeshes[0];
	// If you want to load more than one mesh than change it with a for loop or etc.
	// In obj files there is only 1 mesh

	// Fill vertices positions
	vertices.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		aiVector3D pos = mesh->mVertices[i];
		vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
	}

	// Fill vertices texture coordinates
	uvs.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
		uvs.push_back(glm::vec2(UVW.x, UVW.y));
	}

	// Fill vertices normals
	normals.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		aiVector3D n = mesh->mNormals[i];
		normals.push_back(glm::vec3(n.x, n.y, n.z));
	}

	// Fill face indices
	indices.reserve(3 * mesh->mNumFaces);
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		// Assume the model has only triangles.
		indices.push_back(mesh->mFaces[i].mIndices[0]);
		indices.push_back(mesh->mFaces[i].mIndices[1]);
		indices.push_back(mesh->mFaces[i].mIndices[2]);
	}

	// The "scene" pointer will be deleted automatically by "importer"
	std::printf("Load time: %dms\n", clock() - startTime);

	// Return the baseModel
	return LoadToVAO(vertices, uvs, normals, indices);
}

GLuint Loader::LoadTexture2D(const std::string& fileName)
{
	GLuint texture;
	int width, height;
	glGenTextures(1, &texture);

	// Load image data
	unsigned char* image;
	image = SOIL_load_image(("../Textures/" + fileName + ".png").c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

	// Bind the texture data
	glBindTexture(GL_TEXTURE_2D, texture);

	// Texture the loaded 2D image data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	// Add the image to the textures container
	m_textures.push_back(texture);

	// Clean-up the image data
	SOIL_free_image_data(image);

	// Generate the mipmap texture
	glGenerateMipmap(GL_TEXTURE_2D);

	// Texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// If value is became lower than quality will be high
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// Return the texture id
	return texture;
}

GLuint Loader::CreateVaoID()
{
	GLuint vaoID;

	// Generate vertex array object
	glGenVertexArrays(1, &vaoID);

	// Add vertex array object to the container
	m_vaos.push_back(vaoID);

	// Bind the vertex array object
	glBindVertexArray(vaoID);

	// Return the vertex array object
	return vaoID;
}

void Loader::LoadIndicesToGPU(int indices[], int& count)
{
	GLuint vboID;

	// Generate the vertex buffer object
	glGenBuffers(1, &vboID);

	// Add vertex buffer object to the container
	m_vbos.push_back(vboID);

	// Bind the vertex buffer object to the element array buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);

	// Send the element object with vertex buffer object
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * count, indices, GL_STATIC_DRAW);
}

void Loader::LoadDataToAttributeList(GLuint attribNumber, int attribSize, void* data, int dataSize)
{
	GLuint vboID;

	// Create a new vertex buffer object
	glGenBuffers(1, &vboID);

	// Add vertex buffer object to the container
	m_vbos.push_back(vboID);

	// Bind the vertex buffer object to use it
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	// Load the data to GPU using the vertex buffer object
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

	// Tell OpenGL how and where to store this VBO in the VAO
	glVertexAttribPointer(attribNumber, attribSize, GL_FLOAT, GL_FALSE, 0, nullptr);

	// Unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
