#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL.h>
#include <glm/glm.hpp>

#include "Sprite.hpp"
#include "GameObject.hpp"

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

class Player : public GameObject
{
public:
	Player(const glm::vec2& startPosition, PlayerShipType shipType);

	void update(Uint32 delta);

	void moveLeft();
	void moveRight();
	void stopMovingLeft();
	void stopMovingRight();
	void decelerate();

private:
	void init();
	void setTexCoords();
	void setToStartPosition();

private:
	glm::vec2 m_StartPosition;
	glm::vec2 m_Velocity;

	const float SPEED;

	bool m_MovingLeft;
	bool m_MovingRight;

	PlayerShipType m_ShipType;
	
};

#endif