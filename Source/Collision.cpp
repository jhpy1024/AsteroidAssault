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

	auto rect1Top = rect1.position.y + rect1.height / 2.f;
	auto rect1Bottom = rect1.position.y - rect1.height / 2.f;
	auto rect1Left = rect1.position.x - rect1.width / 2.f;
	auto rect1Right = rect1.position.x + rect1.width / 2.f;

	auto rect2Top = rect2.position.y + rect2.height / 2.f;
	auto rect2Bottom = rect2.position.y - rect2.height / 2.f;
	auto rect2Left = rect2.position.x - rect2.width / 2.f;
	auto rect2Right = rect2.position.x + rect2.width / 2.f;

	return !((rect1Bottom < rect2Top) || (rect1Top > rect2Bottom) || (rect1Left > rect2Right) || (rect1Right < rect2Left));
}

bool Collision::circleVsCircle(const Shape& shape1, const Shape& shape2)
{
	auto circle1 = static_cast<const CircleShape&>(shape1);
	auto circle2 = static_cast<const CircleShape&>(shape2);

	auto pos1 = shape1.position;
	auto pos2 = shape2.position;
	auto distanceSquared = ((pos1.x + pos2.x) * (pos1.x + pos2.x)) + ((pos1.y + pos2.y) * (pos1.y + pos2.y));
	auto sumRadiiSquared = (circle1.radius + circle2.radius) * (circle1.radius + circle2.radius);

	return distanceSquared <= sumRadiiSquared;
}