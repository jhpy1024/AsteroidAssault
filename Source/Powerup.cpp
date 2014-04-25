#include "Powerup.hpp"
#include "Random.hpp"

Powerup::Powerup(const glm::vec2& position, const glm::vec2& velocity, PowerupType::Type type)
	: m_StartPosition(position)
	, m_Velocity(velocity)
	, m_Type(type)
{
	std::vector<float> rotationDirections = { -1.f, 1.f };
	m_RotationSpeed = Random::genFloat(0.18f, 0.36f) * Random::choice(rotationDirections);

	setupSprite();
	setupShape();
}

void Powerup::update(Uint32 delta)
{
	m_Sprite.move(m_Velocity * static_cast<float>(delta));
	m_Sprite.rotateDegs(m_RotationSpeed * static_cast<float>(delta));
	m_Rectangle.position = m_Sprite.getPosition();
}

void Powerup::setupSprite()
{
	m_Sprite.setPosition(m_StartPosition);
	m_Sprite.setTextureBounds(getTextureBounds());
	m_Sprite.setScale({ 2.5f, 2.5f });
}

void Powerup::setupShape()
{
	m_Rectangle = RectangleShape(m_Sprite.getSize());
}

PowerupType::Type Powerup::getType() const
{
	return m_Type;
}

TextureBounds Powerup::getTextureBounds() const
{
	TextureBounds bounds;

	switch (m_Type)
	{
	case PowerupType::Laser:
		bounds.bottomLeft = { 0.f, 0.f };
		bounds.size = { 24.f, 24.f };
		break;
	case PowerupType::Shield:
		bounds.bottomLeft = { 24.f, 0.f };
		bounds.size = { 24.f, 24.f };
		break;
	case PowerupType::Health:
		bounds.bottomLeft = { 48.f, 0.f };
		bounds.size = { 24.f, 24.f };
		break;
	case PowerupType::Lightning:
		bounds.bottomLeft = { 72.f, 0.f };
		bounds.size = { 24.f, 24.f };
		break;
	default:
		break;
	}

	return bounds;
}