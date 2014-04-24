#include "LightningRenderer.hpp"
#include "ShaderManager.hpp"
#include "Random.hpp"

#include <iostream>

LightningRenderer::LightningRenderer()
	: OUTLINE_OFFSET(3.f, 0.f)
{

}

void LightningRenderer::init()
{
	m_VertexBuffer.init();
	m_ColorBuffer.init();
}

void LightningRenderer::render(std::shared_ptr<Lightning> lightning)
{
	std::vector<std::shared_ptr<Lightning>> lightnings;
	lightnings.push_back(lightning);
	render(lightnings);
}

void LightningRenderer::render(std::vector<std::shared_ptr<Lightning>>& lightning)
{
	if (lightning.empty()) return;

	clearVectors();

	for (auto& strike : lightning)
	{
		addVertices(strike);
		addColors(strike);
		addVertices(strike, OUTLINE_OFFSET);
		addColors(strike, { 0.28f, 0.f, 1.f });
		addVertices(strike, -OUTLINE_OFFSET);
		addColors(strike, { 0.28f, 0.f, 1.f });
	}

	passDataToBuffers();

	auto colorShader = ShaderManager::getInstance().getShader("Color");

	m_VertexBuffer.bind();
	colorShader->bind();
	colorShader->setupVertexAttribPointer("in_Position");
	
	m_ColorBuffer.bind();
	colorShader->setupVertexAttribPointer("in_Color", 4);

	glDrawArrays(GL_LINES, 0, m_VertexBuffer.getNumVertices());
}

void LightningRenderer::addVertices(std::shared_ptr<Lightning> lightning, const glm::vec2& offset)
{
	// Add source point
	m_Vertices.push_back(lightning->getPosition().x + offset.x);
	m_Vertices.push_back(lightning->getPosition().y + offset.y);

	for (int i = 0; i < lightning->getMidpoints().size(); ++i)
	{
		auto x = lightning->getMidpoints()[i].x + offset.x;
		auto y = lightning->getMidpoints()[i].y + offset.y;

		m_Vertices.push_back(x);
		m_Vertices.push_back(y);
		m_Vertices.push_back(x);
		m_Vertices.push_back(y);
	}

	// Add target point
	m_Vertices.push_back(lightning->getTargetPosition().x + offset.x);
	m_Vertices.push_back(lightning->getTargetPosition().y + offset.y);
}

void LightningRenderer::addColors(std::shared_ptr<Lightning> lightning, const glm::vec3& color)
{
	for (int i = 0; i < lightning->getMidpoints().size() * 2 + 2; ++i)
	{
		m_Colors.push_back(color.x);
		m_Colors.push_back(color.y);
		m_Colors.push_back(color.z);
		m_Colors.push_back(1.f);
	}
}

void LightningRenderer::clearVectors()
{
	m_Vertices.clear();
	m_Colors.clear();
}

void LightningRenderer::passDataToBuffers()
{
	m_VertexBuffer.setVertices(m_Vertices);
	m_ColorBuffer.setColor(m_Colors);
}