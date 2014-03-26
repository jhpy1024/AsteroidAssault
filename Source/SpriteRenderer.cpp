#include "SpriteRenderer.hpp"
#include "ShaderManager.hpp"

#include <iostream>

SpriteRenderer::SpriteRenderer()
{
	init();
}

void SpriteRenderer::init()
{
	m_VertexBuffer.init();
	m_TexCoordBuffer.init();
}

void SpriteRenderer::render(Sprite& sprite, Texture& texture)
{
	std::vector<Sprite> sprites;
	sprites.push_back(sprite);

	render(sprites, texture);
}

void SpriteRenderer::render(std::vector<Sprite>& sprites, Texture& texture)
{
	if (sprites.empty()) return;

	clearVectors();

	for (auto& sprite : sprites)
	{
		addVertices(sprite.getPosition(), sprite.getSize(), sprite.getRotationRads());
		addTexCoords(sprite.getTextureBounds(), glm::vec2(texture.width, texture.height));
	}
	
	texture.bind();

	passDataToBuffers();
	
	m_VertexBuffer.bind();
	ShaderManager::getInstance().getShader("Texture")->bind();
	ShaderManager::getInstance().getShader("Texture")->setupVertexAttribPointer("in_Position");
	m_TexCoordBuffer.bind();
	ShaderManager::getInstance().getShader("Texture")->setupVertexAttribPointer("in_TexCoords");
	ShaderManager::getInstance().getShader("Texture")->setUniform("in_Texture", texture.getId());
	glDrawArrays(GL_TRIANGLES, 0, m_VertexBuffer.getDataSize());
}

void SpriteRenderer::passDataToBuffers()
{
	m_VertexBuffer.setData(m_Vertices);
	m_TexCoordBuffer.setData(m_TexCoords);
}

void SpriteRenderer::addTexCoords(const TextureBounds& textureBounds, const glm::vec2& textureSize)
{
	// Bottom Left
	m_TexCoords.push_back(textureBounds.bottomLeft.x / textureSize.x);
	m_TexCoords.push_back((textureSize.y - textureBounds.bottomLeft.y) / textureSize.y);

	// Bottom Right
	m_TexCoords.push_back((textureBounds.bottomLeft.x + textureBounds.size.x) / textureSize.x);
	m_TexCoords.push_back((textureSize.y - textureBounds.bottomLeft.y) / textureSize.y);

	// Top Right
	m_TexCoords.push_back((textureBounds.bottomLeft.x + textureBounds.size.x) / textureSize.x);
	m_TexCoords.push_back((textureSize.y - (textureBounds.bottomLeft.y + textureBounds.size.y)) / textureSize.y);

	// Top Right (2)
	m_TexCoords.push_back((textureBounds.bottomLeft.x + textureBounds.size.x) / textureSize.x);
	m_TexCoords.push_back((textureSize.y - (textureBounds.bottomLeft.y + textureBounds.size.y)) / textureSize.y);

	// Top Left
	m_TexCoords.push_back(textureBounds.bottomLeft.x / textureSize.x);
	m_TexCoords.push_back((textureSize.y - (textureBounds.bottomLeft.y + textureBounds.size.y)) / textureSize.y);

	// Bottom Left (2)
	m_TexCoords.push_back(textureBounds.bottomLeft.x / textureSize.x);
	m_TexCoords.push_back((textureSize.y - textureBounds.bottomLeft.y) / textureSize.y);
}

void SpriteRenderer::addVertices(const glm::vec2& position, const glm::vec2& size, float rotationRads)
{
	auto sinAngle = glm::sin(rotationRads);
	auto cosAngle = glm::cos(rotationRads);

	auto offsetFromCenter = glm::vec2(-size.x / 2.f, -size.y / 2.f);
	auto bottomLeft = glm::vec2(position.x + (offsetFromCenter.x * cosAngle - offsetFromCenter.y * sinAngle),
								position.y - (-offsetFromCenter.y * cosAngle - offsetFromCenter.x * sinAngle));

	offsetFromCenter = glm::vec2(size.x / 2.f, -size.y / 2.f);
	auto bottomRight = glm::vec2(position.x + (offsetFromCenter.x * cosAngle - offsetFromCenter.y * sinAngle),
								 position.y - (-offsetFromCenter.y * cosAngle - offsetFromCenter.x * sinAngle));

	offsetFromCenter = glm::vec2(size.x / 2.f, size.y / 2.f);
	auto topRight = glm::vec2(position.x + (offsetFromCenter.x * cosAngle - offsetFromCenter.y * sinAngle),
							  position.y - (-offsetFromCenter.y * cosAngle - offsetFromCenter.x * sinAngle));

	offsetFromCenter = glm::vec2(-size.x / 2.f, size.y / 2.f);
	auto topLeft = glm::vec2(position.x + (offsetFromCenter.x * cosAngle - offsetFromCenter.y * sinAngle),
							 position.y - (-offsetFromCenter.y * cosAngle - offsetFromCenter.x * sinAngle));

	// Bottom Left
	m_Vertices.push_back(bottomLeft.x);
	m_Vertices.push_back(bottomLeft.y);

	// Bottom Right
	m_Vertices.push_back(bottomRight.x);
	m_Vertices.push_back(bottomRight.y);

	// Top Right
	m_Vertices.push_back(topRight.x);
	m_Vertices.push_back(topRight.y);

	// Top Right (2)
	m_Vertices.push_back(topRight.x);
	m_Vertices.push_back(topRight.y);

	// Top Left
	m_Vertices.push_back(topLeft.x);
	m_Vertices.push_back(topLeft.y);

	// Bottom Left (2)
	m_Vertices.push_back(bottomLeft.x);
	m_Vertices.push_back(bottomLeft.y);
}

void SpriteRenderer::clearVectors()
{
	m_Vertices.clear();
	m_TexCoords.clear();
}