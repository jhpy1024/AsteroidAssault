#ifndef MENU_PARTICLE_SYSTEM_HPP
#define MENU_PARTICLE_SYSTEM_HPP

#include "ParticleSystem.hpp"

class MenuParticleSystem : public ParticleSystem
{
public:
	MenuParticleSystem();

	void update(Uint32 delta) override;

private:
	Particle genParticle() override;

	Uint32 m_LastTimeEmitted;
};

#endif