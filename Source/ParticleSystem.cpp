#include "ParticleSystem.hpp"

void ParticleSystem::update(Uint32 delta)
{
	updateParticles(delta);
}

void ParticleSystem::updateParticles(Uint32 delta)
{
	for (auto& particle : m_Particles)
		particle.update(delta);
}