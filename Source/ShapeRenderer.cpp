#include "ShapeRenderer.hpp"
#include "ShaderManager.hpp"
#include "RectangleShape.hpp"

void ShapeRenderer::init()
{
	m_VertexBuffer.init();
	m_ColorBuffer.init();
}

void ShapeRenderer::setNumCircleSegments(int numSegments)
{
	m_NumSegments = numSegments;
}

void ShapeRenderer::render(Shape& shape)
{
	std::vector<Shape> shapes;
	shapes.push_back(shape);
	render(shapes);
}

void ShapeRenderer::render(std::vector<Shape>& shapes)
{
	if (shapes.empty()) return;

	clearVectors();

	for (auto& shape : shapes)
	{
		addVertices(shape);
		addColors(shape);
	}

	passDataToBuffers();

	auto colorShader = ShaderManager::getInstance().getShader("Color");

	m_VertexBuffer.bind();
	colorShader->bind();
	colorShader->setupVertexAttribPointer("in_Position");
	
	m_ColorBuffer.bind();
	colorShader->setupVertexAttribPointer("in_Color", 4);

	glDrawArrays(GL_TRIANGLES, 0, m_VertexBuffer.getNumVertices());
}

void ShapeRenderer::addVertices(Shape& shape)
{
	switch (shape.getType())
	{
	case ShapeType::Rectangle:
		addVertices(static_cast<RectangleShape&>(shape));
		break;
	case ShapeType::Circle:
		addVertices(static_cast<CircleShape&>(shape));
		break;
	default:
		break;
	}
}

void ShapeRenderer::addColors(Shape& shape)
{
	switch (shape.getType())
	{
	case ShapeType::Rectangle:
		addColors(static_cast<RectangleShape&>(shape));
		break;
	case ShapeType::Circle:
		addColors(static_cast<CircleShape&>(shape));
		break;
	default:
		break;
	}
}

void ShapeRenderer::addVertices(RectangleShape& shape)
{
	// Bottom Left
	m_Vertices.push_back(shape.position.x - shape.width / 2.f);
	m_Vertices.push_back(shape.position.y - shape.height / 2.f);

	// Bottom Right
	m_Vertices.push_back(shape.position.x + shape.width / 2.f);
	m_Vertices.push_back(shape.position.y - shape.height / 2.f);

	// Top Right
	m_Vertices.push_back(shape.position.x + shape.width / 2.f);
	m_Vertices.push_back(shape.position.y + shape.height / 2.f);

	// Top Right (2)
	m_Vertices.push_back(shape.position.x + shape.width / 2.f);
	m_Vertices.push_back(shape.position.y + shape.height / 2.f);

	// Top Left
	m_Vertices.push_back(shape.position.x - shape.width / 2.f);
	m_Vertices.push_back(shape.position.y + shape.height / 2.f);

	// Bottom Left (2)
	m_Vertices.push_back(shape.position.x - shape.width / 2.f);
	m_Vertices.push_back(shape.position.y - shape.height / 2.f);
}

void ShapeRenderer::addVertices(CircleShape& shape)
{
	for (int i = 0; i < m_NumSegments; ++i)
	{
		float theta = 2.f * 3.1415926f * i * m_NumSegments;

		float x = shape.radius * std::cos(theta);
		float y = shape.radius * std::sin(theta);

		m_Vertices.push_back(x);
		m_Vertices.push_back(y);
	}
}

void ShapeRenderer::addColors(RectangleShape& shape)
{
	for (int i = 0; i < 6; ++i)
	{
		m_Colors.push_back(1.f);
		m_Colors.push_back(0.f);
		m_Colors.push_back(0.f);
		m_Colors.push_back(1.f);
	}
}

void ShapeRenderer::addColors(CircleShape& shape)
{
	for (int i = 0; i < m_NumSegments; ++i)
	{
		m_Colors.push_back(1.f);
		m_Colors.push_back(0.f);
		m_Colors.push_back(0.f);
		m_Colors.push_back(1.f);
	}
}

void ShapeRenderer::clearVectors()
{
	m_Vertices.clear();
	m_Colors.clear();
}

void ShapeRenderer::passDataToBuffers()
{
	m_VertexBuffer.setVertices(m_Vertices);
	m_ColorBuffer.setColor(m_Colors);
}
