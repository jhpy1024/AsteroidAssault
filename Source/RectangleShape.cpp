#include "RectangleShape.hpp"

RectangleShape::RectangleShape()
	: Shape(ShapeType::Rectangle)
	, width(0.f)
	, height(0.f)
{

}

RectangleShape::RectangleShape(float width, float height)
	: Shape(ShapeType::Rectangle)
	, width(width)
	, height(height)
{

}