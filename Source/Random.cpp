#include "Random.hpp"

std::random_device Random::m_RandomDevice;

float Random::genFloat(float lowerBound, float upperBound)
{
	std::default_random_engine engine(m_RandomDevice());
	std::uniform_real_distribution<float> distribution(lowerBound, upperBound);

	return distribution(engine);
}

int Random::genInt(int lowerBound, int upperBound)
{
	std::default_random_engine engine(m_RandomDevice());
	std::uniform_int_distribution<int> distribution(lowerBound, upperBound);

	return distribution(engine);
}