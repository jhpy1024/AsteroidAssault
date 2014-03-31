#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Sprite.hpp"
#include "RectangleShape.hpp"

class GameObject
{
public:
	GameObject();

	Sprite& getSprite();
	RectangleShape& getShape();

	bool shouldRemove() const;
	void flagForRemoval();

protected:
	Sprite m_Sprite;
	RectangleShape m_Rectangle;

	bool m_ShouldRemove;
};

#endif