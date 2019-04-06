#include "../pch.h"
#include "ObjFileLoader.hpp"


BaseModel ObjFileLoader::LoadAssimpObjFile(const std::string & fileName, Loader & loader)
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
	std::string path = "../Models/" + fileName + ".obj";

	const aiScene* scene = importer.ReadFile(path, aiProcess_JoinIdenticalVertices | aiProcess_SortByPType | aiProcess_ConvertToLeftHanded);
	if (!scene) {
		fprintf(stderr, importer.GetErrorString());
		getchar();
	}

	const aiMesh* mesh = scene->mMeshes[0];
	// If you want to load more than one mesh than change it with a for loop or etc.
	// In obj files there is only 1 mesh

	// Fill vertices positions
	vertices.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D pos = mesh->mVertices[i];
		vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
	}

	// Fill vertices texture coordinates
	uvs.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
		uvs.push_back(glm::vec2(UVW.x, UVW.y));
	}

	// Fill vertices normals
	normals.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D n = mesh->mNormals[i];
		normals.push_back(glm::vec3(n.x, n.y, n.z));
	}

	// Fill face indices
	indices.reserve(3 * mesh->mNumFaces);
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		// Assume the model has only triangles.
		indices.push_back(mesh->mFaces[i].mIndices[0]);
		indices.push_back(mesh->mFaces[i].mIndices[1]);
		indices.push_back(mesh->mFaces[i].mIndices[2]);
	}

	// The "scene" pointer will be deleted automatically by "importer"
	std::printf("Load time: %dms\n", clock() - startTime);

	// Return the baseModel
	//return loader.LoadToVAO(vertices, uvs, normals, indices);
	return loader.LoadToVAO(vertices, uvs, indices);
}

Model ObjFileLoader::LoadModel(const std::string & modelFile, const std::string & textureFile, Loader & loader)
{
	BaseModel tempBaseModel(LoadAssimpObjFile(modelFile, loader));

	Texture tempTexture(loader.LoadTexture2D(textureFile));

	Model returnModel(tempBaseModel, tempTexture);

	return returnModel;
}
