#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>

#include "Player.hpp"
#include "Texture.hpp"
#include "Sprite.hpp"
#include "SpriteRenderer.hpp"

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
	void setupSprites();
	void setupDefaultMatrices();

	void handleKeyPress(SDL_Keycode key);
	void handleKeyRelease(SDL_Keycode key);

public:
	static int WIDTH;
	static int HEIGHT;

private:
	Player m_Player;
	
	Sprite m_Background;

	SpriteRenderer m_SpriteRenderer;
};

#endif