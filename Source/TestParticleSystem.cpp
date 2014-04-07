#include "TestParticleSystem.hpp"
#include "Random.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"

#include <iostream>

TestParticleSystem::TestParticleSystem()
	: ParticleSystem("Particle")
	, m_LastTimeGenerated(0)
	, m_EmissionDelay(0)
	, m_EmissionCount(10)
{
	m_TextureBounds.bottomLeft = glm::vec2(0.f);
	m_TextureBounds.size = glm::vec2(5.f);
}

void TestParticleSystem::setEmissionCount(int count)
{
	m_EmissionCount = count;
}

void TestParticleSystem::emitParticles()
{
	for (int i = 0; i < m_EmissionCount; ++i)
	{
		m_Particles.push_back(genParticle());
	}
}

void TestParticleSystem::update(Uint32 delta)
{
	ParticleSystem::update(delta);

	/*if (SDL_GetTicks() - m_LastTimeGenerated >= m_EmissionDelay)
	{
		for (int i = 0; i < 5; ++i)
			m_Particles.push_back(genParticle());
	}*/
}

Particle TestParticleSystem::genParticle()
{
	auto position = glm::vec2(Random::genFloat(0.f, Game::WIDTH), Random::genFloat(0.f, Game::HEIGHT));
	auto velX = glm::sin(Random::genFloat(0.f, 2.f * 3.14159f));
	auto velY = glm::cos(Random::genFloat(0.f, 2.f * 3.14159f));
	auto velocity = glm::vec2(velX, velY);
	auto lifetime = Random::genInt(100, 500);

	m_LastTimeGenerated = SDL_GetTicks();

	Particle particle(m_Position, velocity, lifetime);
	particle.color = glm::vec4(Random::genFloat(0.f, 1.f), Random::genFloat(0.f, 1.f), Random::genFloat(0.f, 1.f), 1.f);

	return particle;
}
