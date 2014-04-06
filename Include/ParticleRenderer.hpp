#ifndef PARTICLE_RENDERER_HPP
#define PARTICLE_RENDERER_HPP

#include <vector>

#include "Buffer.hpp"
#include "ParticleSystem.hpp"

class ParticleRenderer
{
public:
	void init();
	void render(ParticleSystem& particleSystem);

private:
	void clearVectors();

	void addVertices(const glm::vec2& position, const glm::vec2& size, float rotationRads);
	void addTexCoords(const TextureBounds& textureBounds, const glm::vec2& textureSize);
	void addColors(const Particle& particle);

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