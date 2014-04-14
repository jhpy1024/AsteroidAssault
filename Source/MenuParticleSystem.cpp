#include "MenuParticleSystem.hpp"
#include "Random.hpp"
#include "Game.hpp"

#include <iostream>

MenuParticleSystem::MenuParticleSystem()
	: ParticleSystem("Particle")
	, m_LastTimeEmitted(0)
{
	m_TextureBounds.bottomLeft = { 0.f, 0.f };
	m_TextureBounds.size = { 5.f, 5.f };
}

void MenuParticleSystem::update(Uint32 delta)
{
	ParticleSystem::update(delta);

	for (auto& particle : m_Particles)
	{
		if ((particle.size.x > 0.f) && (particle.size.y > 0.f))
		{
			particle.size.x -= (m_Texture.width * 1.5f) / particle.getLifetime();
			particle.size.y -= (m_Texture.height * 1.5f) / particle.getLifetime();
		}
	}

	if (SDL_GetTicks() - m_LastTimeEmitted >= Random::genInt(500, 2500))
		emitParticles();
}

Particle MenuParticleSystem::genParticle()
{
	auto position = glm::vec2(Random::genFloat(0.f, Game::WIDTH), Random::genFloat(0.f, Game::HEIGHT));

	auto lifetime = Random::genInt(500, 3000);
	auto size = glm::vec2(m_Texture.width * 1.5f, m_Texture.height * 1.5f);
	auto rotation = Random::genFloat(0.f, 360.f);

	Particle particle(position, { 0.f, 0.f }, size, lifetime);
	particle.color = glm::vec4(1.f, 1.f, 1.f, Random::genFloat(0.2f, 0.7f));
	particle.setRotationDegs(rotation);

	m_LastTimeEmitted = SDL_GetTicks();

	return particle;
}