#include "Asteroid.hpp"

Asteroid::Asteroid()
	: m_Velocity(getRandomVelocity())
	, m_RotationSpeed(getRandomRotationSpeed())
	, m_Speed(getRandomSpeed())
	, m_Type(getRandomType())
{
	setupSprite();
}

void Asteroid::update(Uint32 delta)
{

}

void Asteroid::setupSprite()
{

}

AsteroidType::Type Asteroid::getRandomType() const
{
	return AsteroidType::BrownBig1;
}

glm::vec2 Asteroid::getRandomPosition() const
{
	return glm::vec2(0.f);
}

glm::vec2 Asteroid::getRandomVelocity() const
{
	return glm::vec2(0.f);
}

float Asteroid::getRandomRotationSpeed() const
{
	return 0.f;
}

float Asteroid::getRandomSpeed() const
{
	return 0.f;
}