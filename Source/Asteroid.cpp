#include "Asteroid.hpp"
#include "Random.hpp"
#include "Game.hpp"

Asteroid::Asteroid()
	: m_Velocity(getRandomVelocity())
	, m_RotationSpeed(getRandomRotationSpeed())
	, m_Speed(getRandomSpeed())
	, m_Type(getRandomType())
{
	setupSprite();
}

void Asteroid::update(Uint32 delta)
{
	m_Sprite.move(m_Velocity * m_Speed * static_cast<float>(delta));
	m_Sprite.rotateDegs(m_RotationSpeed * static_cast<float>(delta));
}

void Asteroid::setupSprite()
{
	m_Sprite.setPosition(getRandomPosition());
	m_Sprite.setTextureBounds(getTextureBounds());
}

Sprite& Asteroid::getSprite()
{
	return m_Sprite;
}

TextureBounds Asteroid::getTextureBounds() const
{
	TextureBounds textureBounds;

	switch (m_Type)
	{
	case AsteroidType::BrownBig1:
		textureBounds.bottomLeft = glm::vec2(0.f);
		textureBounds.size = glm::vec2(101.f, 84.f);
		break;
	case AsteroidType::BrownBig2:
		textureBounds.bottomLeft = glm::vec2(103.f, 0.f);
		textureBounds.size = glm::vec2(120.f, 98.f);
		break;
	case AsteroidType::BrownBig3:
		textureBounds.bottomLeft = glm::vec2(225.f, 0.f);
		textureBounds.size = glm::vec2(89.f, 82.f);
		break;
	case AsteroidType::BrownBig4:
		textureBounds.bottomLeft = glm::vec2(316.f, 0.f);
		textureBounds.size = glm::vec2(98.f, 96.f);
		break;
	case AsteroidType::BrownMed1:
		textureBounds.bottomLeft = glm::vec2(416.f, 0.f);
		textureBounds.size = glm::vec2(43.f, 43.f);
		break;
	case AsteroidType::BrownMed2:
		textureBounds.bottomLeft = glm::vec2(461.f, 0.f);
		textureBounds.size = glm::vec2(45.f, 40.f);
		break;
	case AsteroidType::BrownSmall1:
		textureBounds.bottomLeft = glm::vec2(508.f, 0.f);
		textureBounds.size = glm::vec2(28.f, 28.f);
		break;
	case AsteroidType::BrownSmall2:
		textureBounds.bottomLeft = glm::vec2(538.f, 0.f);
		textureBounds.size = glm::vec2(29.f, 26.f);
		break;
	default:
		break;
	}

	return textureBounds;
}

AsteroidType::Type Asteroid::getRandomType() const
{
	int numTypes = AsteroidType::Last - 1;
	int randomType = Random::genInt(0, numTypes);

	return static_cast<AsteroidType::Type>(randomType);
}

glm::vec2 Asteroid::getRandomPosition() const
{
	glm::vec2 position;

	position.x = Random::genFloat(0.f, Game::WIDTH);
	position.y = Game::HEIGHT * 1.2f;

	return position;
}

glm::vec2 Asteroid::getRandomVelocity() const
{
	auto randomAngle = Random::genFloat(90.f, 180.f);
	auto angleRads = glm::radians(randomAngle);

	return glm::vec2(glm::sin(angleRads), glm::cos(angleRads));
}

float Asteroid::getRandomRotationSpeed() const
{
	return Random::genFloat(-15.f, 15.f) / 1000.f;
}

float Asteroid::getRandomSpeed() const
{
	return Random::genFloat(15.f, 30.f) / 1000.f;
}