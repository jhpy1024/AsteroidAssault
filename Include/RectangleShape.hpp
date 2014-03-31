#ifndef RECTANGLE_SHAPE_HPP
#define RECTANGLE_SHAPE_HPP

#include "Shape.hpp"

class RectangleShape : public Shape
{
public:
	RectangleShape();
	RectangleShape(const glm::vec2& size);
	RectangleShape(float width, float height);

public:
	float width;
	float height;
};

#endif