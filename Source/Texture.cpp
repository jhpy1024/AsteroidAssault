#include "Texture.hpp"

#include <SOIL.h>

Texture::Texture(const std::string& fileName)
	: m_FileName(fileName)
{
	generateTexture();
	bind();
	setWrapping();
	setFiltering();
	generateMipmap();

	auto textureData = loadTextureData();
	createTexture(textureData);
	SOIL_free_image_data(textureData);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_Texture);
}

void Texture::generateTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &m_Texture);
}

void Texture::setWrapping()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Texture::setFiltering()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::generateMipmap()
{
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::createTexture(unsigned char* textureData)
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
}

unsigned char* Texture::loadTextureData()
{
	return SOIL_load_image("Resources/Textures/TestTexture.png", &width, &height, 0, SOIL_LOAD_RGBA);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_Texture);
}