#ifndef TEXTURE_BOUNDS_HPP
#define TEXTURE_BOUNDS_HPP

#include <glm/glm.hpp>

struct TextureBounds
{
	glm::vec2 bottomLeft;
	glm::vec2 bottomRight;
	glm::vec2 topLeft;
	glm::vec2 topRight;
};

#endif