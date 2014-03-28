#ifndef LASER_HPP
#define LASER_HPP

#include <SDL.h>

#include "Sprite.hpp"

enum class LaserType
{
	Red,
	Green,
	Blue,
	Yellow,
	Pink,
};

class Laser
{
public:
	Laser(const glm::vec2& position, float angleDegs, LaserType type);

	void update(Uint32 delta);

	Sprite& getSprite();

private:
	void setVelocity();
	void setupSprite();
	TextureBounds getTextureBounds() const;

private:
	Sprite m_Sprite;

	glm::vec2 m_StartPosition;
	glm::vec2 m_Velocity;
	float m_Angle;

	const float SPEED;

	LaserType m_Type;
};

#endif