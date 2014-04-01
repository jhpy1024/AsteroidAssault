#include "Player.hpp"

Player::Player(const glm::vec2& startPosition, PlayerShipType shipType)
	: m_StartPosition(startPosition)
	, m_ShipType(shipType)
	, m_MovingLeft(false)
	, m_MovingRight(false)
	, SPEED(500.f / 1000.f)
{
	init();
}

void Player::init()
{
	setTexCoords();
	setToStartPosition();
}

void Player::update(Uint32 delta)
{
	if (m_MovingLeft)
		m_Velocity.x = -1.f;
	else if (m_MovingRight)
		m_Velocity.x = 1.f;
	else
		decelerate();

	m_Sprite.move(m_Velocity * SPEED * static_cast<float>(delta));
}

void Player::moveLeft()
{
	m_MovingLeft = true;
}

void Player::moveRight()
{
	m_MovingRight = true;
}

void Player::stopMovingLeft()
{
	m_MovingLeft = false;
}

void Player::stopMovingRight()
{
	m_MovingRight = false;
}

void Player::decelerate()
{
	m_Velocity.x *= 0.95f;
}

void Player::setToStartPosition()
{
	m_Sprite.setPosition(m_StartPosition);
}

void Player::setTexCoords()
{
	TextureBounds textureBounds;

	switch (m_ShipType)
	{
	case PlayerShipType::BlueRectangular:
		textureBounds.bottomLeft = glm::vec2(0.f, 0.f);
		textureBounds.size = glm::vec2(99.f, 75.f);
		break;
	case PlayerShipType::GreenRectangular:
		textureBounds.bottomLeft = glm::vec2(101.f, 0.f);
		textureBounds.size = glm::vec2(99.f, 75.f);
		break;
	case PlayerShipType::OrangeRectangular:
		textureBounds.bottomLeft = glm::vec2(202.f, 0.f);
		textureBounds.size = glm::vec2(99.f, 75.f);
		break;
	case PlayerShipType::RedRectangular:
		textureBounds.bottomLeft = glm::vec2(302.f, 0.f);
		textureBounds.size = glm::vec2(99.f, 75.f);
		break;
	case PlayerShipType::BluePointed:
		textureBounds.bottomLeft = glm::vec2(0.f, 77.f);
		textureBounds.size = glm::vec2(112.f, 75.f);
		break;
	case PlayerShipType::GreenPointed:
		textureBounds.bottomLeft = glm::vec2(114.f, 77.f);
		textureBounds.size = glm::vec2(112.f, 75.f);
		break;
	case PlayerShipType::OrangePointed:
		textureBounds.bottomLeft = glm::vec2(228.f, 77.f);
		textureBounds.size = glm::vec2(112.f, 75.f);
		break;
	case PlayerShipType::RedPointed:
		textureBounds.bottomLeft = glm::vec2(342.f, 77.f);
		textureBounds.size = glm::vec2(112.f, 75.f);
		break;
	default:
		break;
	}

	m_Sprite.setTextureBounds(textureBounds);
}