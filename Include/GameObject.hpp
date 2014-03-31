#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Sprite.hpp"
#include "RectangleShape.hpp"

class GameObject
{
public:
	Sprite& getSprite();
	RectangleShape& getShape();

protected:
	Sprite m_Sprite;
	RectangleShape m_Rectangle;
};

#endif