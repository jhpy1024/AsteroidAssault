#ifndef ASTEROID_FACTORY_HPP
#define ASTEROID_FACTORY_HPP

#include <vector>
#include <memory>

#include "Asteroid.hpp"

class AsteroidFactory
{
public:
	static std::vector<std::shared_ptr<Asteroid>> createSubAsteroids(Asteroid& asteroid);

private:
	static AsteroidType::Type getSubType(AsteroidType::Type type);

	static AsteroidType::Type getRandomMedBrown();
	static AsteroidType::Type getRandomSmallBrown();
	static AsteroidType::Type getRandomMedGrey();
	static AsteroidType::Type getRandomSmallGrey();

	static glm::vec2 getRandomOffset();

	static void createAsteroids(std::vector<std::shared_ptr<Asteroid>>& asteroids, const glm::vec2& position, AsteroidType::Type type);

	static const int NUM_MEDIUM;
	static const int NUM_SMALL;
	static const int NUM_SUB_ASTEROIDS;
	static const float MIN_OFFSET;
	static const float MAX_OFFSET;
};

#endif