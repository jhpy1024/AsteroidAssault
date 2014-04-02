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
	Asteroid(const glm::vec2& position, AsteroidType::Type type);

	void update(Uint32 delta);

	AsteroidType::Type getType() const;

private:
	AsteroidType::Type getRandomType() const;
	glm::vec2 getRandomPosition() const;
	glm::vec2 getRandomVelocity() const;
	float getRandomRotationSpeed() const;
	float getRandomSpeed() const;

	void setupSprite();
	void setupShape();

	TextureBounds getTextureBounds() const;

private:
	glm::vec2 m_StartPosition;
	glm::vec2 m_Velocity;
	float m_RotationSpeed;
	float m_Speed;

	AsteroidType::Type m_Type;

	static const float SUB_ASTEROID_SPEED_FACTOR;
	static const float SUB_ASTEROID_VELOCITY_FACTOR;
	static const float SUB_ASTEROID_ROTATION_SPEED_FACTOR;

};

#endif