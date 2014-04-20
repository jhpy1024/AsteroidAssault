#ifndef SHAPE_RENDERER_HPP
#define SHAPE_RENDERER_HPP

#include "Shape.hpp"
#include "Buffer.hpp"
#include "RectangleShape.hpp"
#include "CircleShape.hpp"

#include <vector>
#include <memory>

class ShapeRenderer
{
public:
	ShapeRenderer();

	void init();
	void render(std::shared_ptr<Shape> shape);
	void render(std::vector<std::shared_ptr<Shape>>& shapes);

	void setNumCircleSegments(int numSegments);

private:
	void clearVectors();

	void addVertices(std::shared_ptr<Shape> shape);
	void addVertices(std::shared_ptr<RectangleShape> shape);
	void addVertices(std::shared_ptr<CircleShape> shape);

	void addColors(std::shared_ptr<Shape> shape);
	void addColors(std::shared_ptr<RectangleShape> shape);
	void addColors(std::shared_ptr<CircleShape> shape);

	void passDataToBuffers();

private:
	Buffer m_VertexBuffer;
	Buffer m_ColorBuffer;

	std::vector<float> m_Vertices;
	std::vector<float> m_Colors;

	int m_NumSegments;
};

#endif