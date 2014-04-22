#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <vector>

class Random
{
public:
	static float genFloat(float lowerBound, float upperBound);
	static int genInt(int lowerBound, int upperBound);

	template <typename T>
	static T choice(const std::vector<T>& choices);

private:
	static std::random_device m_RandomDevice;
};

#include "Random.inl"

#endif