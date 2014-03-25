#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>

class Game
{
public:
	Game(int width, int height);

	void init();

	void handleEvent(const SDL_Event& event);
	void update(Uint32 delta);
	void render();

public:
	static int WIDTH;
	static int HEIGHT;
};

#endif