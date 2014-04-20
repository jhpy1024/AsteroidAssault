#include "RectangleShape.hpp"

#include <iostream>

RectangleShape::RectangleShape()
	: Shape(ShapeType::Rectangle)
	, width(0.f)
	, height(0.f)
{
}

RectangleShape::RectangleShape(const glm::vec2& size)
	: Shape(ShapeType::Rectangle)
	, width(size.x)
	, height(size.y)
{
}

RectangleShape::RectangleShape(float width, float height)
	: Shape(ShapeType::Rectangle)
	, width(width)
	, height(height)
{
}