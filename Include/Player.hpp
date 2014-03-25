#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL.h>
#include <glm/glm.hpp>

#include "Sprite.hpp"

enum class PlayerShipType
{
	BluePointed,
	GreenPointed,
	OrangePointed,
	RedPointed,

	BlueRectangular,
	GreenRectangular,
	OrangeRectangular,
	RedRectangular,
};

class Player
{
public:
	Player(const glm::vec2& startPosition, PlayerShipType shipType);

	void update(Uint32 delta);

	Sprite& getSprite();

private:
	void init();
	void setTexCoords();
	void setToStartPosition();

private:
	Sprite m_Sprite;

	glm::vec2 m_StartPosition;
	glm::vec2 m_Velocity;

	PlayerShipType m_ShipType;
};

#endif