#ifndef SHAPE_HPP
#define SHAPE_HPP

enum class ShapeType
{
	Circle,
	Rectangle,
};

class Shape
{
public:
	ShapeType getType() const;

protected:
	Shape(ShapeType type);

private:
	ShapeType m_Type;
};

#endif