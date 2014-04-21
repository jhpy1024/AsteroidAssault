#ifndef MATH_UTILS_HPP
#define MATH_UTILS_HPP

class MathUtils
{
public:
	static float clamp(float x, float lowerBound, float upperBound);
	static float smoothStep(float x, float lowerBound, float upperBound);
};

#endif