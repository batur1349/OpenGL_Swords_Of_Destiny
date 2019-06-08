#ifndef TILETEXTUREPACK_HPP
#define TILETEXTUREPACK_HPP

#include "Texture.hpp"

class TileTexturePack
{
public:
	TileTexturePack(const std::map<std::string, Texture>& textures);

	// Getters
	inline Texture& GetTexture(const std::string& textureName) { return _textures[textureName]; }
private:
	// Container
	std::map<std::string, Texture> _textures;
};

#endif // !TILETEXTUREPACK_HPP