#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "Shape.hpp"
#include "CircleShape.hpp"
#include "RectangleShape.hpp"

class Collision
{
public:
	static bool isColliding(const Shape& shape1, const Shape& shape2);

private:
	static bool circleVsCircle(const Shape& shape1, const Shape& shape2);
	static bool rectangleVsRectangle(const Shape& shape1, const Shape& shape2);
};

#endif