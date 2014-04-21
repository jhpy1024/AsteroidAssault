#ifndef POWERUP_HPP
#define POWERUP_HPP

#include "GameObject.hpp"

#include <SDL.h>

namespace PowerupType
{
	enum Type
	{
		Laser,
		Shield,
		Last,
	};
};

class Powerup : public GameObject
{
public:
	Powerup(const glm::vec2& position, const glm::vec2& velocity, PowerupType::Type type);

	void update(Uint32 delta);

	PowerupType::Type getType() const;

private:
	void setupSprite();
	void setupShape();

	TextureBounds getTextureBounds() const;

private:
	PowerupType::Type m_Type;

	glm::vec2 m_StartPosition;
	glm::vec2 m_Velocity;
};

#endif