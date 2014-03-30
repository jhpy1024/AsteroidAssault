#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <glm/glm.hpp>

enum class ShapeType
{
	Circle,
	Rectangle,
};

class Shape
{
public:
	ShapeType getType() const;

	glm::vec2 position;

protected:
	Shape(ShapeType type);

private:
	ShapeType m_Type;
};

#endif