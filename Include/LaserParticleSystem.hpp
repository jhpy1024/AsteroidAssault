#ifndef LASER_PARTICLE_SYSTEM_HPP
#define LASER_PARTICLE_SYSTEM_HPP

#include "ParticleSystem.hpp"

class LaserParticleSystem : public ParticleSystem
{
public:
	LaserParticleSystem();

	void update(Uint32 delta) override;

private:
	Particle genParticle() override;
};

#endif