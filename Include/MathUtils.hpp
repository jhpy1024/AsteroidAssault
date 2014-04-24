#ifndef MATH_UTILS_HPP
#define MATH_UTILS_HPP

#include <glm/glm.hpp>

class MathUtils
{
public:
	static float clamp(float x, float lowerBound, float upperBound);
	static float smoothStep(float x, float lowerBound, float upperBound);
	static glm::vec2 midpoint(const glm::vec2& a, const glm::vec2& b);
};

#endif