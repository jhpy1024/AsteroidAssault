#include "Shape.hpp"

Shape::Shape(ShapeType type)
	: m_Type(type)
{

}

ShapeType Shape::getType() const
{
	return m_Type;
}