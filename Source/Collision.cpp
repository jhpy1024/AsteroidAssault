#include "Collision.hpp"

#include <iostream>

bool Collision::isColliding(const Shape& shape1, const Shape& shape2)
{
	auto shape1Type = shape1.getType();
	auto shape2Type = shape2.getType();

	if ((shape1Type == ShapeType::Rectangle) && (shape2Type == ShapeType::Rectangle))
		return rectangleVsRectangle(shape1, shape2);
	else if ((shape1Type == ShapeType::Circle) && (shape2Type == ShapeType::Circle))
		return circleVsCircle(shape1, shape2);
	else
	{
		std::cerr << "This form of collision detection has not been implemented yet." << std::endl;
		return false;
	}
}

bool Collision::rectangleVsRectangle(const Shape& shape1, const Shape& shape2)
{
	auto rect1 = static_cast<const RectangleShape&>(shape1);
	auto rect2 = static_cast<const RectangleShape&>(shape2);
}

bool Collision::circleVsCircle(const Shape& shape1, const Shape& shape2)
{
	auto circle1 = static_cast<const CircleShape&>(shape1);
	auto circle2 = static_cast<const CircleShape&>(shape2);
}