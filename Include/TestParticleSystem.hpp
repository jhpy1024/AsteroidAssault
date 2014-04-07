#ifndef TEST_PARTICLE_SYSTEM_HPP
#define TEST_PARTICLE_SYSTEM_HPP

#include "ParticleSystem.hpp"

class TestParticleSystem : public ParticleSystem
{
public:
	TestParticleSystem();

	void update(Uint32 delta) override;

	void emitParticles();
	void setEmissionCount(int count);

private:
	Particle genParticle() override;

private:
	Uint32 m_LastTimeGenerated;
	Uint32 m_EmissionDelay;

	int m_EmissionCount;
};

#endif