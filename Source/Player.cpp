#include "Player.hpp"

Player::Player(const glm::vec2& startPosition, PlayerShipType shipType)
	: m_StartPosition(startPosition)
	, m_ShipType(shipType)
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
	case PlayerShipType::BluePointed:
		textureBounds.bottomLeft = glm::vec2(0.f, 0.f);
		textureBounds.size = glm::vec2(99.f, 75.f);
		break;
	case PlayerShipType::GreenPointed:
		textureBounds.bottomLeft = glm::vec2(101.f, 0.f);
		textureBounds.size = glm::vec2(99.f, 75.f);
		break;
	case PlayerShipType::OrangePointed:
		textureBounds.bottomLeft = glm::vec2(202.f, 0.f);
		textureBounds.size = glm::vec2(99.f, 75.f);
		break;
	case PlayerShipType::RedPointed:
		textureBounds.bottomLeft = glm::vec2(302.f, 0.f);
		textureBounds.size = glm::vec2(99.f, 75.f);
		break;
	case PlayerShipType::BlueRectangular:
		textureBounds.bottomLeft = glm::vec2(0.f, 77.f);
		textureBounds.size = glm::vec2(112.f, 75.f);
		break;
	case PlayerShipType::GreenRectangular:
		textureBounds.bottomLeft = glm::vec2(114.f, 77.f);
		textureBounds.size = glm::vec2(112.f, 75.f);
		break;
	case PlayerShipType::OrangeRectangular:
		textureBounds.bottomLeft = glm::vec2(228.f, 77.f);
		textureBounds.size = glm::vec2(112.f, 75.f);
		break;
	case PlayerShipType::RedRectangular:
		textureBounds.bottomLeft = glm::vec2(342.f, 77.f);
		textureBounds.size = glm::vec2(112.f, 75.f);
		break;
	default:
		break;
	}

	m_Sprite.setTextureBounds(textureBounds);
}

Sprite& Player::getSprite()
{
	return m_Sprite;
}