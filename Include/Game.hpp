#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>
#include <memory>

#include "State.hpp"

class Game
{
public:
	Game(int width, int height);

	void init();

	void handleEvent(const SDL_Event& event);
	void update(Uint32 delta);
	void render();

private:
	void loadShaders();
	void loadTextures();
	void loadAudio();
	void setupDefaultMatrices();

	void handleKeyPress(SDL_Keycode key);
	void handleKeyRelease(SDL_Keycode key);
	
public:
	static int WIDTH;
	static int HEIGHT;
};

#endif