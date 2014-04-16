#include "Powerup.hpp"

Powerup::Powerup(const glm::vec2& position, const glm::vec2& velocity, PowerupType::Type type)
	: m_StartPosition(position)
	, m_Velocity(velocity)
	, m_Type(type)
{
	setupSprite();
	setupShape();
}

void Powerup::update(Uint32 delta)
{
	m_Sprite.move(m_Velocity * static_cast<float>(delta));
	m_Rectangle.position = m_Sprite.getPosition();
}

void Powerup::setupSprite()
{
	m_Sprite.setPosition(m_StartPosition);
	m_Sprite.setTextureBounds(getTextureBounds());
}

void Powerup::setupShape()
{
	m_Rectangle = RectangleShape(m_Sprite.getSize());
}

TextureBounds Powerup::getTextureBounds() const
{
	TextureBounds bounds;

	switch (m_Type)
	{
	case PowerupType::Laser:
		bounds.bottomLeft = { 0.f, 0.f };
		bounds.size = { 61.f, 60.f };
		break;
	default:
		break;
	}

	return bounds;
}