#include "Laser.hpp"
#include "Game.hpp"

Laser::Laser(const glm::vec2& position, float angleDegs, LaserType type)
	: m_StartPosition(position)
	, m_Angle(angleDegs)
	, m_Type(type)
	, SPEED(Game::HEIGHT / 1000.f)
{
	setVelocity();
	setupSprite();
}

void Laser::update(Uint32 delta)
{
	m_Sprite.move(m_Velocity * SPEED * static_cast<float>(delta));
}

void Laser::setVelocity()
{
	float angleRads = glm::radians(m_Angle);

	m_Velocity.x = glm::sin(angleRads);
	m_Velocity.y = glm::cos(angleRads);
}

void Laser::setupSprite()
{
	m_Sprite.setPosition(m_StartPosition);
	m_Sprite.setTextureBounds(getTextureBounds());
}

TextureBounds Laser::getTextureBounds() const
{
	TextureBounds textureBounds;
	textureBounds.size = glm::vec2(9.f, 37.f);

	switch (m_Type)
	{
	case LaserType::Blue:
		textureBounds.bottomLeft = glm::vec2(0.f);
		break;
	case LaserType::Green:
		textureBounds.bottomLeft = glm::vec2(12.f, 0.f);
		break;
	case LaserType::Red:
		textureBounds.bottomLeft = glm::vec2(23.f, 0.f);
		break;
	case LaserType::Pink:
		textureBounds.bottomLeft = glm::vec2(35.f, 0.f);
		break;
	case LaserType::Yellow:
		textureBounds.bottomLeft = glm::vec2(47.f, 0.f);
		break;
	default:
		break;
	}

	return textureBounds;
}