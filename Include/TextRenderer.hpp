#ifndef TEXT_RENDERER_HPP
#define TEXT_RENDERER_HPP

#include "Text.hpp"
#include "Texture.hpp"
#include "Buffer.hpp"
#include "TextureBounds.hpp"

#include <vector>

class TextRenderer
{
public:
	void init();
	void render(Text& text, Texture& texture);
	void render(std::vector<Text>& texts, Texture& texture);

private:
	void clearVectors();

	void addVertices(const glm::vec2& position, const glm::vec2& size, float rotationRads);
	void addTexCoords(const TextureBounds& textureBounds, const glm::vec2& textureSize);
	void addColors(const Text& text);

	void passDataToBuffers();

private:
	Buffer m_VertexBuffer;
	Buffer m_TexCoordBuffer;
	Buffer m_ColorBuffer;

	std::vector<float> m_Vertices;
	std::vector<float> m_TexCoords;
	std::vector<float> m_Colors;
};

#endif