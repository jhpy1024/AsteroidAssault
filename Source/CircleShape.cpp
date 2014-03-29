#include "CircleShape.hpp"

CircleShape::CircleShape()
	: Shape(ShapeType::Circle)
	, radius(0.f)
{
	
}

CircleShape::CircleShape(float radius)
	: Shape(ShapeType::Circle)
	, radius(radius)
{

}