#ifndef CIRCLE_SHAPE_HPP
#define CIRCLE_SHAPE_HPP

#include "Shape.hpp"

class CircleShape : public Shape
{
public:
	CircleShape();
	CircleShape(float radius);

public:
	float radius;
};

#endif