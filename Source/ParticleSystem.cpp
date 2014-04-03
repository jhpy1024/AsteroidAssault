#include "ParticleSystem.hpp"

// TODO
// ===================================================================
// Implement this!
// I'm thinking of creating a ParticleRenderer class that handles the
// rendering of particles, as they're different from sprites and so 
// SpriteRenderer shouldn't really be used.
// ===================================================================
void ParticleSystem::render()
{

}

void ParticleSystem::update(Uint32 delta)
{
	updateParticles(delta);
}

void ParticleSystem::updateParticles(Uint32 delta)
{
	for (auto& particle : m_Particles)
		particle.update(delta);
}