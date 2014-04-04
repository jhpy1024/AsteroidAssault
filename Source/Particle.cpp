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

void Particle::rotateRads(float rotation)
{
	m_RotationRads += rotation;
}

void Particle::rotateDegs(float rotation)
{
	m_RotationRads += glm::radians(rotation);
}

void Particle::setRotationRads(float rotation)
{
	m_RotationRads = rotation;
}

void Particle::setRotationDegs(float rotation)
{
	m_RotationRads = glm::radians(rotation);
}

float Particle::getRotationRads() const
{
	return m_RotationRads;
}

float Particle::getRotationDegs() const
{
	return glm::degrees(m_RotationRads);
}

bool Particle::isAlive() const
{
	auto currentTime = SDL_GetTicks();
	auto elapsedTime = currentTime - m_TimeCreated;

	return elapsedTime <= m_Lifetime;
}