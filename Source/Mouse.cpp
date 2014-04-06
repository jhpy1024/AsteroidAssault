#include "Mouse.hpp"
#include "Game.hpp"

#include <SDL.h>

glm::vec2 Mouse::getPosition()
{
	return { getX(), getY() };
}

float Mouse::getX()
{
	int x;
	SDL_GetMouseState(&x, NULL);

	return x;
}

float Mouse::getY()
{
	int y;
	SDL_GetMouseState(NULL, &y);

	return Game::HEIGHT - y;
}