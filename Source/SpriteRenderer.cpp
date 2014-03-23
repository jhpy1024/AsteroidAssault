#include "SpriteRenderer.hpp"
#include "ShaderManager.hpp"

SpriteRenderer::SpriteRenderer()
{
	
}

void SpriteRenderer::init()
{
	m_VertexBuffer.init();
	m_TexCoordBuffer.init();
}

void SpriteRenderer::render(std::vector<Sprite>& sprites)
{
	clearVectors();

	for (auto& sprite : sprites)
	{
		addVertices(sprite.getPosition(), sprite.getSize());
		addTexCoords(sprite.getTextureBounds(), sprite.getTextureSize());

		sprite.bindTexture();
	}

	passDataToBuffers();
	
	m_VertexBuffer.bind();
	ShaderManager::getInstance().getShader("Texture")->bind();
	ShaderManager::getInstance().getShader("Texture")->setupVertexAttribPointer("in_Position");
	m_TexCoordBuffer.bind();
	ShaderManager::getInstance().getShader("Texture")->setupVertexAttribPointer("in_TexCoords");
	ShaderManager::getInstance().getShader("Texture")->setUniform("in_Texture", 0);

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
	m_TexCoords.push_back(textureBounds.bottomRight.x / textureSize.x);
	m_TexCoords.push_back((textureSize.y - textureBounds.bottomRight.y) / textureSize.y);

	// Top Right
	m_TexCoords.push_back(textureBounds.topRight.x / textureSize.x);
	m_TexCoords.push_back((textureSize.y - textureBounds.topRight.y) / textureSize.y);

	// Top Right (2)
	m_TexCoords.push_back(textureBounds.topRight.x / textureSize.x);
	m_TexCoords.push_back((textureSize.y - textureBounds.topRight.y) / textureSize.y);

	// Top Left
	m_TexCoords.push_back(textureBounds.topLeft.x / textureSize.x);
	m_TexCoords.push_back((textureSize.y - textureBounds.topLeft.y) / textureSize.y);

	// Bottom Left (2)
	m_TexCoords.push_back(textureBounds.bottomLeft.x / textureSize.x);
	m_TexCoords.push_back((textureSize.y - textureBounds.bottomLeft.y) / textureSize.y);
}

void SpriteRenderer::addVertices(const glm::vec2& position, const glm::vec2& size)
{
	// Bottom Left
	m_Vertices.push_back(position.x - size.x / 2.f);
	m_Vertices.push_back(position.y - size.y / 2.f);

	// Bottom Right
	m_Vertices.push_back(position.x + size.x / 2.f);
	m_Vertices.push_back(position.y - size.y / 2.f);

	// Top Right
	m_Vertices.push_back(position.x + size.x / 2.f);
	m_Vertices.push_back(position.y + size.y / 2.f);

	// Top Right (2)
	m_Vertices.push_back(position.x + size.x / 2.f);
	m_Vertices.push_back(position.y + size.y / 2.f);

	// Top Left
	m_Vertices.push_back(position.x - size.x / 2.f);
	m_Vertices.push_back(position.y + size.y / 2.f);

	// Bottom Left (2)
	m_Vertices.push_back(position.x - size.x / 2.f);
	m_Vertices.push_back(position.y - size.y / 2.f);
}

void SpriteRenderer::clearVectors()
{
	m_Vertices.clear();
	m_TexCoords.clear();
}