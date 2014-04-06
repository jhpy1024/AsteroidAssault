#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <glm/glm.hpp>

class Mouse
{
public:
	static glm::vec2 getPosition();
	static float getX();
	static float getY();
};

#endif