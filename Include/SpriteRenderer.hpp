#ifndef SPRITE_RENDERER_HPP
#define SPRITE_RENDERER_HPP

#include "Buffer.hpp"
#include "Sprite.hpp"
#include "TextureBounds.hpp"
#include "Texture.hpp"

class SpriteRenderer
{
public:
	SpriteRenderer();

	void render(std::vector<Sprite>& sprites, Texture& texture);

private:
	void init();
	void clearVectors();
	void addVertices(const glm::vec2& position, const glm::vec2& size, float rotationRads);
	void addTexCoords(const TextureBounds& textureBounds, const glm::vec2& textureSize);
	void passDataToBuffers();

private:
	Buffer m_VertexBuffer;
	Buffer m_TexCoordBuffer;

	std::vector<float> m_Vertices;
	std::vector<float> m_TexCoords;
};

#endif