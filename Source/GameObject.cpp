#include "GameObject.hpp"

GameObject::GameObject()
	: m_ShouldRemove(false)
{

}

void GameObject::flagForRemoval()
{
	m_ShouldRemove = true;
}

bool GameObject::shouldRemove() const
{
	return m_ShouldRemove;
}

Sprite& GameObject::getSprite()
{
	return m_Sprite;
}

RectangleShape& GameObject::getShape()
{
	return m_Rectangle;
}