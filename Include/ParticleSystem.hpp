#ifndef PARTICLE_SYSTEM_HPP
#define PARTICLE_SYSTEM_HPP

#include <SDL.h>

#include <vector>

#include "Particle.hpp"
#include "Texture.hpp"
#include "TextureBounds.hpp"

// TODO
// =======================================================================
// The texture needs to be initialized after all the textures are created.
// Ideas
// -----
// -> init() function in particle system
// =======================================================================

class ParticleSystem
{
	friend class ParticleRenderer;

public:
	virtual void update(Uint32 delta);

protected:
	virtual Particle genParticle() = 0;
	void updateParticles(Uint32 delta);
	
protected:
	std::vector<Particle> m_Particles;

	Texture m_Texture;
	TextureBounds m_TextureBounds;
};

#endif