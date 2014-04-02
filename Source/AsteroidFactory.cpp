#include "AsteroidFactory.hpp"
#include "Random.hpp"

const int AsteroidFactory::NUM_MEDIUM = 2;
const int AsteroidFactory::NUM_SMALL = 2;
const int AsteroidFactory::NUM_SUB_ASTEROIDS = 3;
const float AsteroidFactory::MIN_OFFSET = -30.f;
const float AsteroidFactory::MAX_OFFSET = 30.f;

std::vector<std::shared_ptr<Asteroid>> AsteroidFactory::createSubAsteroids(Asteroid& asteroid)
{
	std::vector<std::shared_ptr<Asteroid>> subAsteroids;

	auto position = asteroid.getSprite().getPosition();
	auto type = asteroid.getType();
	auto subType = getSubType(type);
	
	if (subType != AsteroidType::Last)
		createAsteroids(subAsteroids, position, subType);

	return subAsteroids;
}

void AsteroidFactory::createAsteroids(std::vector<std::shared_ptr<Asteroid>>& asteroids, const glm::vec2& position, AsteroidType::Type type)
{
	for (int i = 0; i < NUM_SUB_ASTEROIDS; ++i)
	{
		auto newPosition = position + getRandomOffset();
		asteroids.push_back(std::make_shared<Asteroid>(position, type));
	}
}

glm::vec2 AsteroidFactory::getRandomOffset()
{
	auto x = Random::genFloat(MIN_OFFSET, MAX_OFFSET);
	auto y = Random::genFloat(MIN_OFFSET, MAX_OFFSET);

	return glm::vec2(x, y);
}

AsteroidType::Type AsteroidFactory::getSubType(AsteroidType::Type type)
{
	AsteroidType::Type subType;

	switch (type)
	{
	case AsteroidType::BrownBig1:
	case AsteroidType::BrownBig2:
	case AsteroidType::BrownBig3:
	case AsteroidType::BrownBig4:
		subType = getRandomMedBrown();
		break;
	case AsteroidType::GreyBig1:
	case AsteroidType::GreyBig2:
	case AsteroidType::GreyBig3:
	case AsteroidType::GreyBig4:
		subType = getRandomMedGrey();
		break;
	case AsteroidType::BrownMed1:
	case AsteroidType::BrownMed2:
		subType = getRandomSmallBrown();
		break;
	case AsteroidType::GreyMed1:
	case AsteroidType::GreyMed2:
		subType = getRandomSmallGrey();
		break;
	default:
		subType = AsteroidType::Last;
		break;
	}

	return subType;
}

AsteroidType::Type AsteroidFactory::getRandomMedBrown()
{
	auto randomType = AsteroidType::BrownMed1 + Random::genInt(0, NUM_MEDIUM - 1);
	return static_cast<AsteroidType::Type>(randomType);
}

AsteroidType::Type AsteroidFactory::getRandomMedGrey()
{
	auto randomType = AsteroidType::GreyMed1 + Random::genInt(0, NUM_MEDIUM - 1);
	return static_cast<AsteroidType::Type>(randomType);
}

AsteroidType::Type AsteroidFactory::getRandomSmallBrown()
{
	auto randomType = AsteroidType::BrownSmall1 + Random::genInt(0, NUM_SMALL - 1);
	return static_cast<AsteroidType::Type>(randomType);
}

AsteroidType::Type AsteroidFactory::getRandomSmallGrey()
{
	auto randomType = AsteroidType::GreySmall1 + Random::genInt(0, NUM_SMALL - 1);
	return static_cast<AsteroidType::Type>(randomType);
}