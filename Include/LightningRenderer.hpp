#ifndef LIGHTNING_RENDERER_HPP
#define LIGHTNING_RENDERER_HPP

#include "Lightning.hpp"
#include "Buffer.hpp"

#include <vector>
#include <memory>

class LightningRenderer
{
public:
	void init();

	void render(std::shared_ptr<Lightning> lightning);
	void render(std::vector<std::shared_ptr<Lightning>>& lightning);

private:
	void clearVectors();
	void passDataToBuffers();

	void addVertices(std::shared_ptr<Lightning> lightning);
	void addColors(std::shared_ptr<Lightning> lightning);

private:
	Buffer m_VertexBuffer;
	Buffer m_ColorBuffer;

	std::vector<float> m_Vertices;
	std::vector<float> m_Colors;
};

#endif