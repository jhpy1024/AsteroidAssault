#ifndef STAR_PARTICLE_SYSTEM_HPP
#define STAR_PARTICLE_SYSTEM_HPP

#include "ParticleSystem.hpp"

class StarParticleSystem : public ParticleSystem
{
public:
	StarParticleSystem(const glm::vec3& starColor = { 1.f, 1.f, 1.f });

	void update(Uint32 delta) override;

private:
	Particle genParticle() override;

	Uint32 m_LastTimeEmitted;

	glm::vec3 m_StarColor;
};

#endif