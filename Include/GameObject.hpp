#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Sprite.hpp"

class GameObject
{
public:
	Sprite& getSprite();

protected:
	Sprite m_Sprite;
};

#endif