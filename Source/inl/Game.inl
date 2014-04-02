#ifndef GAME_INL
#define GAME_INL

#include <memory>
#include <vector>

#include "Sprite.hpp"

template <typename T>
std::vector<Sprite> Game::getSpritesFromCollection(std::vector<std::shared_ptr<T>>& collection)
{
	std::vector<Sprite> sprites;

	for (auto& element : collection)
		sprites.push_back(element->getSprite());

	return sprites;
}

#endif