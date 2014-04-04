#include "TestParticleSystem.hpp"
#include "Random.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"

TestParticleSystem::TestParticleSystem()
	: m_LastTimeGenerated(0)
	, m_EmissionDelay(50)
{
	m_Texture = TextureManager::getInstance().getTexture("Particle");
	m_TextureBounds.bottomLeft = glm::vec2(0.f);
	m_TextureBounds.size = glm::vec2(5.f);
}

void TestParticleSystem::update(Uint32 delta)
{
	if (SDL_GetTicks() - m_LastTimeGenerated >= m_EmissionDelay)
		genParticle();

	for (auto& particle : m_Particles)
		particle.update(delta);
}

Particle TestParticleSystem::genParticle()
{
	auto position = glm::vec2(Random::genFloat(0.f, Game::WIDTH), Random::genFloat(0.f, Game::HEIGHT));
	auto velX = glm::sin(Random::genFloat(0.f, 3.14159f));
	auto velY = glm::cos(Random::genFloat(0.f, 3.14159f));
	auto velocity = glm::vec2(velX, velY);
	auto lifetime = Random::genInt(100, 500);

	m_LastTimeGenerated = SDL_GetTicks();

	return Particle(position, velocity, lifetime);
}
