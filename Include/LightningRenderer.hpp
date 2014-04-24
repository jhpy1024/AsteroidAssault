#ifndef LIGHTNING_RENDERER_HPP
#define LIGHTNING_RENDERER_HPP

#include "Lightning.hpp"
#include "Buffer.hpp"

#include <vector>
#include <memory>

class LightningRenderer
{
public:
	LightningRenderer();

	void init();

	void render(std::shared_ptr<Lightning> lightning);
	void render(std::vector<std::shared_ptr<Lightning>>& lightning);

private:
	void clearVectors();
	void passDataToBuffers();

	void addVertices(std::shared_ptr<Lightning> lightning, const glm::vec2& offset = glm::vec2(0.f, 0.f));
	void addColors(std::shared_ptr<Lightning> lightning, const glm::vec3& color = glm::vec3(1.f, 1.f, 1.f));

private:
	Buffer m_VertexBuffer;
	Buffer m_ColorBuffer;

	std::vector<float> m_Vertices;
	std::vector<float> m_Colors;

	const glm::vec2 OUTLINE_OFFSET;
};

#endif