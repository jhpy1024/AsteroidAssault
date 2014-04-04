#include "Buffer.hpp"

Buffer::Buffer()
{
	
}

void Buffer::init()
{
	glGenBuffers(1, &m_Buffer);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &m_Buffer);
}

void Buffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
}

void Buffer::setVertices(const std::vector<float>& vertices)
{
	bind();

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	m_NumVertices = vertices.size() / 2;
}

int Buffer::getNumVertices() const
{
	return m_NumVertices;
}