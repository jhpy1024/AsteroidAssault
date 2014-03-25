#include "TextureManager.hpp"

#include <cassert>

std::unique_ptr<TextureManager> TextureManager::m_Instance;

TextureManager::TextureManager()
{
}

void TextureManager::addTexture(const std::string& id, const std::string& fileName)
{
	m_Textures[id] = std::make_shared<Texture>(fileName);
}

Texture& TextureManager::getTexture(const std::string& id)
{
	assert(m_Textures.find(id) != m_Textures.end());

	return *m_Textures[id];
}

TextureManager& TextureManager::getInstance()
{
	if (m_Instance == nullptr)
		m_Instance = std::unique_ptr<TextureManager>(new TextureManager);

	return *m_Instance;
}