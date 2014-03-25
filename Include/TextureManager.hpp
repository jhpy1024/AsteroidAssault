#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include "Texture.hpp"

#include <map>
#include <string>
#include <memory>

class TextureManager
{
public:
	static TextureManager& getInstance();

	void addTexture(const std::string& id, const std::string& fileName);
	Texture& getTexture(const std::string& id);

private:
	TextureManager();

private:
	static std::unique_ptr<TextureManager> m_Instance;

	std::map<std::string, std::shared_ptr<Texture>> m_Textures;
};

#endif