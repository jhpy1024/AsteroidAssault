#ifndef PARTICLE_SYSTEM_HPP
#define PARTICLE_SYSTEM_HPP

#include <SDL.h>

#include <vector>

#include "Particle.hpp"

class ParticleSystem
{
public:
	virtual void update(Uint32 delta);

	void render();

protected:
	virtual Particle genParticle() = 0;
	void updateParticles(Uint32 delta);
	
protected:
	std::vector<Particle> m_Particles;
};

#endif