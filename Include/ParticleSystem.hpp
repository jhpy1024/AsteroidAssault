#ifndef PARTICLE_SYSTEM_HPP
#define PARTICLE_SYSTEM_HPP

#include <SDL.h>

#include <glm/glm.hpp>

#include <vector>

#include "Particle.hpp"
#include "Texture.hpp"
#include "TextureBounds.hpp"

class ParticleSystem
{
	friend class ParticleRenderer;

public:
	ParticleSystem(const std::string& textureId);

	virtual void update(Uint32 delta);

	void move(const glm::vec2& offset);
	void setPosition(const glm::vec2& position);

	void emitParticles();
	void setEmissionCount(int count);

protected:
	virtual Particle genParticle() = 0;
	void updateParticles(Uint32 delta);
	void removeDeadParticles();
	
protected:
	std::vector<Particle> m_Particles;

	Texture& m_Texture;
	TextureBounds m_TextureBounds;

	glm::vec2 m_Position;

	int m_EmissionCount;
};

#endif