#ifndef OBJFILELOADER_HPP
#define OBJFILELOADER_HPP

#include "Loader.hpp"
#include "../Model/Model.hpp"

class ObjFileLoader
{
public:
	static BaseModel LoadAssimpObjFile(const std::string& fileName, Loader& loader);
	static Model LoadModel(const std::string& modelFile, const std::string& textureFile, Loader& loader);
};

#endif // !OBJFILELOADER_HPP