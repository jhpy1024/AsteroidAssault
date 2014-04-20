#include "ShapeRenderer.hpp"
#include "ShaderManager.hpp"
#include "Shader.hpp"
#include "RectangleShape.hpp"

#include <iostream>

ShapeRenderer::ShapeRenderer()
	: m_NumSegments(100)
{

}

void ShapeRenderer::init()
{
	m_VertexBuffer.init();
	m_ColorBuffer.init();
}

void ShapeRenderer::setNumCircleSegments(int numSegments)
{
	m_NumSegments = numSegments;
}

void ShapeRenderer::render(std::shared_ptr<Shape> shape)
{
	std::vector<std::shared_ptr<Shape>> shapes;
	shapes.push_back(shape);
	render(shapes);
}

void ShapeRenderer::render(std::vector<std::shared_ptr<Shape>>& shapes)
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

	glDrawArrays(GL_TRIANGLE_FAN, 0, m_VertexBuffer.getNumVertices());
}

void ShapeRenderer::addVertices(std::shared_ptr<Shape> shape)
{
	switch (shape->getType())
	{
	case ShapeType::Rectangle:
		addVertices(std::static_pointer_cast<RectangleShape>(shape));
		break;
	case ShapeType::Circle:
		addVertices(std::static_pointer_cast<CircleShape>(shape));
		break;
	default:
		break;
	}
}

void ShapeRenderer::addColors(std::shared_ptr<Shape> shape)
{
	switch (shape->getType())
	{
	case ShapeType::Rectangle:
		addColors(std::static_pointer_cast<RectangleShape>(shape));
		break;
	case ShapeType::Circle:
		addColors(std::static_pointer_cast<CircleShape>(shape));
		break;
	default:
		break;
	}
}

void ShapeRenderer::addVertices(std::shared_ptr<RectangleShape> shape)
{
	// Bottom Left
	m_Vertices.push_back(shape->position.x - shape->width / 2.f);
	m_Vertices.push_back(shape->position.y - shape->height / 2.f);

	// Bottom Right
	m_Vertices.push_back(shape->position.x + shape->width / 2.f);
	m_Vertices.push_back(shape->position.y - shape->height / 2.f);

	// Top Right
	m_Vertices.push_back(shape->position.x + shape->width / 2.f);
	m_Vertices.push_back(shape->position.y + shape->height / 2.f);

	// Top Right (2)
	m_Vertices.push_back(shape->position.x + shape->width / 2.f);
	m_Vertices.push_back(shape->position.y + shape->height / 2.f);

	// Top Left
	m_Vertices.push_back(shape->position.x - shape->width / 2.f);
	m_Vertices.push_back(shape->position.y + shape->height / 2.f);

	// Bottom Left (2)
	m_Vertices.push_back(shape->position.x - shape->width / 2.f);
	m_Vertices.push_back(shape->position.y - shape->height / 2.f);
}

void ShapeRenderer::addVertices(std::shared_ptr<CircleShape> shape)
{
	float prevX;
	float prevY;

	for (int i = 0; i < m_NumSegments; ++i)
	{
		float theta = (2.f * 3.1415926f * i) / m_NumSegments;

		float x = shape->radius * std::cos(theta) + shape->position.x;
		float y = shape->radius * std::sin(theta) + shape->position.y;

		m_Vertices.push_back(x);
		m_Vertices.push_back(y);
	}
}

void ShapeRenderer::addColors(std::shared_ptr<RectangleShape> shape)
{
	for (int i = 0; i < 6; ++i)
	{
		m_Colors.push_back(1.f);
		m_Colors.push_back(1.f);
		m_Colors.push_back(1.f);
		m_Colors.push_back(1.f);
	}
}

void ShapeRenderer::addColors(std::shared_ptr<CircleShape> shape)
{
	for (int i = 0; i < (m_NumSegments * 3) - 1; ++i)
	{
		m_Colors.push_back(0.f);
		m_Colors.push_back(1.f);
		m_Colors.push_back(1.f);
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
