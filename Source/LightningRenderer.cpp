#include "LightningRenderer.hpp"
#include "ShaderManager.hpp"
#include "Random.hpp"

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

void LightningRenderer::addVertices(std::shared_ptr<Lightning> lightning)
{
	// Add source point
	m_Vertices.push_back(lightning->getPosition().x);
	m_Vertices.push_back(lightning->getPosition().y);

	for (int i = 0; i < lightning->getMidpoints().size(); ++i)
	{
		auto x = lightning->getMidpoints()[i].x;
		auto y = lightning->getMidpoints()[i].y;

		m_Vertices.push_back(x);
		m_Vertices.push_back(y);
		m_Vertices.push_back(x);
		m_Vertices.push_back(y);
	}

	// Add target point
	m_Vertices.push_back(lightning->getTargetPosition().x);
	m_Vertices.push_back(lightning->getTargetPosition().y);
}

void LightningRenderer::addColors(std::shared_ptr<Lightning> lightning)
{
	for (int i = 0; i < lightning->getMidpoints().size() * 9; ++i)
	{
		m_Colors.push_back(1.f);
		m_Colors.push_back(1.f);
		m_Colors.push_back(1.f);
		m_Colors.push_back(Random::genFloat(0.5f, 1.f));
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