#ifndef EXPLOSION_PARTICLE_SYSTEM_HPP
#define EXPLOSION_PARTICLE_SYSTEM_HPP

#include "ParticleSystem.hpp"

class ExplosionParticleSystem : public ParticleSystem
{
public:
	ExplosionParticleSystem();
	
	void update(Uint32 delta) override;

private:
	Particle genParticle() override;

private:
	Uint32 m_LastTimeGenerated;
	Uint32 m_EmissionDelay;
};

#endif