#include "ParticleRenderer.hpp"
#include "ShaderManager.hpp"

#include <iostream>

void ParticleRenderer::init()
{
	m_VertexBuffer.init();
	m_TexCoordBuffer.init();
}

void ParticleRenderer::render(ParticleSystem& particleSystem)
{
	auto& particles = particleSystem.m_Particles;
	auto& texture = particleSystem.m_Texture;
	auto& textureBounds = particleSystem.m_TextureBounds;

	auto textureSize = glm::vec2(texture.width, texture.height);

	if (particles.empty()) return;

	clearVectors();

	for (auto& particle : particles)
	{
		addVertices(particle.position, textureSize, particle.getRotationRads());
		addTexCoords(textureBounds, textureSize);
	}

	texture.bind();

	passDataToBuffers();

	m_VertexBuffer.bind();
	ShaderManager::getInstance().getShader("Texture")->bind();
	ShaderManager::getInstance().getShader("Texture")->setupVertexAttribPointer("in_Position");
	m_TexCoordBuffer.bind();
	ShaderManager::getInstance().getShader("Texture")->setupVertexAttribPointer("in_TexCoords");
	ShaderManager::getInstance().getShader("Texture")->setUniform("in_Texture", texture.getId());
	glDrawArrays(GL_TRIANGLES, 0, m_VertexBuffer.getNumVertices());
}

void ParticleRenderer::addVertices(const glm::vec2& position, const glm::vec2& size, float rotationRads)
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

void ParticleRenderer::addTexCoords(const TextureBounds& textureBounds, const glm::vec2& textureSize)
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

void ParticleRenderer::passDataToBuffers()
{
	m_VertexBuffer.setVertices(m_Vertices);
	m_TexCoordBuffer.setVertices(m_TexCoords);
}

void ParticleRenderer::clearVectors()
{
	m_Vertices.clear();
	m_TexCoords.clear();
}