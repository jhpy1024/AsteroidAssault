#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <glm/glm.hpp>

#include <SDL.h>

#include "GameObject.hpp"
#include "TextureBounds.hpp"

namespace AsteroidType
{
	enum Type
	{
		BrownBig1,
		BrownBig2,
		BrownBig3,
		BrownBig4,
		GreyBig1,
		GreyBig2,
		GreyBig3,
		GreyBig4,
		BrownMed1,
		BrownMed2,
		GreyMed1,
		GreyMed2,
		BrownSmall1,
		BrownSmall2,
		GreySmall1,
		GreySmall2,
		Last,
	};
}

class Asteroid : public GameObject
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

	TextureBounds getTextureBounds() const;

private:
	glm::vec2 m_Velocity;
	float m_RotationSpeed;
	float m_Speed;

	AsteroidType::Type m_Type;
};

#endif