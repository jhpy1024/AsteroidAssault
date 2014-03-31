#ifndef LASER_HPP
#define LASER_HPP

#include <SDL.h>

#include "GameObject.hpp"

enum class LaserType
{
	Red,
	Green,
	Blue,
	Yellow,
	Pink,
};

class Laser : public GameObject
{
public:
	Laser(const glm::vec2& position, float angleDegs, LaserType type);

	void update(Uint32 delta);

private:
	void setVelocity();
	void setupSprite();
	void setupShape();
	TextureBounds getTextureBounds() const;

private:
	glm::vec2 m_StartPosition;
	glm::vec2 m_Velocity;
	float m_Angle;

	const float SPEED;

	LaserType m_Type;
};

#endif