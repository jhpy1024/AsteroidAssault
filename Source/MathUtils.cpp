#include "MathUtils.hpp"

float MathUtils::clamp(float x, float lowerBound, float upperBound)
{
	if (x < lowerBound)
		return lowerBound;
	else if (x > upperBound)
		return upperBound;
	else
		return x;
}

float MathUtils::smoothStep(float x, float lowerBound, float upperBound)
{
	float x1 = clamp((x - lowerBound) / (upperBound - lowerBound), 0.f, 1.f);
	return x1 * x1 * (3 - 2 * x1);
}

glm::vec2 MathUtils::midpoint(const glm::vec2& a, const glm::vec2& b)
{
	return glm::vec2((a.x + b.x) / 2.f, (a.y + b.y) / 2.f);
}