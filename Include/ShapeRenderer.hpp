#ifndef SHAPE_RENDERER_HPP
#define SHAPE_RENDERER_HPP

#include "Shape.hpp"
#include "Buffer.hpp"
#include "RectangleShape.hpp"
#include "CircleShape.hpp"

#include <vector>

class ShapeRenderer
{
public:
	void init();
	void render(Shape& shape);
	void render(std::vector<Shape>& shapes);

	void setNumCircleSegments(int numSegments);

private:
	void clearVectors();

	void addVertices(Shape& shape);
	void addVertices(RectangleShape& shape);
	void addVertices(CircleShape& shape);

	void addColors(Shape& shape);
	void addColors(RectangleShape& shape);
	void addColors(CircleShape& shape);

	void passDataToBuffers();

private:
	Buffer m_VertexBuffer;
	Buffer m_ColorBuffer;

	std::vector<float> m_Vertices;
	std::vector<float> m_Colors;

	int m_NumSegments;
};

#endif