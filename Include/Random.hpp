#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

class Random
{
public:
	static float genFloat(float lowerBound, float upperBound);
	static int genInt(int lowerBound, int upperBound);

private:
	static std::random_device m_RandomDevice;
};

#endif