#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <glm/glm.hpp>

#include <SDL.h>

#include "Sprite.hpp"

namespace AsteroidType
{
	enum Type
	{
		BrownBig1,
		BrownBig2,
		BrownBig3,
		BrownBig4,
		BrownMed1,
		BrownMed2,
		BrownSmall1,
		BrownSmall2,
	};
}

class Asteroid
{
public:
	Asteroid();

	void update(Uint32 delta);

private:
	AsteroidType::Type getRandomType() const;
	glm::vec2 getRandomPosition() const;
	glm::vec2 getRandomVelocity() const;
	float getRandomRotationSpeed() const;
	float getRandomSpeed() const;

	void setupSprite();

private:
	Sprite m_Sprite;

	glm::vec2 m_Velocity;
	float m_RotationSpeed;
	float m_Speed;

	AsteroidType::Type m_Type;
};

#endif