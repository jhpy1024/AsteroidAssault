#ifndef SPRITE_RENDERER_HPP
#define SPRITE_RENDERER_HPP

#include "Buffer.hpp"
#include "Sprite.hpp"

class SpriteRenderer
{
public:
	SpriteRenderer();

	void init();
	void render(std::vector<Sprite>& sprites);

private:
	void clearVectors();
	void addVertices(const glm::vec2& position, const glm::vec2& size);
	void addTexCoords();
	void passDataToBuffers();

private:
	Buffer m_VertexBuffer;
	Buffer m_TexCoordBuffer;

	std::vector<float> m_Vertices;
	std::vector<float> m_TexCoords;
};

#endif