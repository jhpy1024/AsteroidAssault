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
	else if ((shape1Type == ShapeType::Circle) && (shape2Type == ShapeType::Rectangle))
		return circleVsRectangle(shape1, shape2);
	else if ((shape2Type == ShapeType::Circle) && (shape1Type == ShapeType::Rectangle))
		return circleVsRectangle(shape2, shape1);
}

bool Collision::circleVsRectangle(const Shape& shape1, const Shape& shape2)
{
	auto circle = static_cast<const CircleShape&>(shape1);
	auto rect = static_cast<const RectangleShape&>(shape2);

	float circleDistanceX = std::abs(circle.position.x - rect.position.x);
	float circleDistanceY = std::abs(circle.position.y - rect.position.y);

	if (circleDistanceX > (rect.width / 2 + circle.radius)) { return false; }
	if (circleDistanceY > (rect.height / 2 + circle.radius)) { return false; }

	if (circleDistanceX <= (rect.width / 2)) { return true; }
	if (circleDistanceY <= (rect.height / 2)) { return true; }

	float cornerDistanceSquared = (circleDistanceX - rect.width / 2) * (circleDistanceX - rect.width / 2) +
		(circleDistanceY - rect.height / 2) * (circleDistanceY - rect.height / 2);

	return (cornerDistanceSquared <= (circle.radius * circle.radius));
}

bool Collision::rectangleVsRectangle(const Shape& shape1, const Shape& shape2)
{
	auto rect1 = static_cast<const RectangleShape&>(shape1);
	auto rect2 = static_cast<const RectangleShape&>(shape2);

	if (std::abs(rect1.position.x - rect2.position.x) <= rect1.width / 2.f + rect2.width / 2.f)
	{
		if (std::abs(rect1.position.y - rect2.position.y) <= rect1.height / 2.f + rect2.height / 2.f)
			return true;
	}

	return false;
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