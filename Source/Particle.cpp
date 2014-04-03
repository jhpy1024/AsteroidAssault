#include "Particle.hpp"

Particle::Particle(const glm::vec2& position, const glm::vec2& velocity, Uint32 lifetime, const glm::vec4& color)
	: position(position)
	, velocity(velocity)
	, color(color)
	, m_Lifetime(lifetime)
	, m_TimeCreated(SDL_GetTicks())
{

}

void Particle::update(Uint32 delta)
{
	position += velocity * static_cast<float>(delta);
}

bool Particle::isAlive() const
{
	auto currentTime = SDL_GetTicks();
	auto elapsedTime = currentTime - m_TimeCreated;

	return elapsedTime <= m_Lifetime;
}