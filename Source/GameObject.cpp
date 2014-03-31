#include "GameObject.hpp"

Sprite& GameObject::getSprite()
{
	return m_Sprite;
}

RectangleShape& GameObject::getShape()
{
	return m_Rectangle;
}