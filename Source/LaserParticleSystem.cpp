#include "LaserParticleSystem.hpp"
#include "Random.hpp"
#include "Game.hpp"

LaserParticleSystem::LaserParticleSystem()
	: ParticleSystem("Particle")
{
	m_TextureBounds.bottomLeft = glm::vec2(0.f);
	m_TextureBounds.size = glm::vec2(5.f);
}

void LaserParticleSystem::update(Uint32 delta)
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
}

Particle LaserParticleSystem::genParticle()
{
	auto position = glm::vec2(Random::genFloat(0.f, Game::WIDTH), Random::genFloat(0.f, Game::HEIGHT));
	// LOOKS PRETTY COOL :D
	auto velX = glm::sin(Random::genFloat(0.f, 0.f));
	auto velY = glm::cos(Random::genFloat(0.f, 3.14159f));
	/*auto velX = glm::sin(Random::genFloat(glm::radians(150.f), glm::radians(210.f)));
	auto velY = glm::sin(Random::genFloat(glm::radians(150.f), glm::radians(210.f)));*/
	auto velocity = glm::vec2(velX, velY);
	auto lifetime = Random::genInt(100, 500);
	auto size = glm::vec2(m_Texture.width * 1.5f, m_Texture.height * 1.5f);
	auto rotation = Random::genFloat(0.f, 360.f);

	//m_LastTimeGenerated = SDL_GetTicks();

	Particle particle(m_Position, velocity, size, lifetime);
	particle.color = glm::vec4(1.f, Random::genFloat(0.f, 0.2f), Random::genFloat(0.f, 0.2f), Random::genFloat(0.2f, 0.7f));
	particle.setRotationDegs(rotation);

	return particle;
}