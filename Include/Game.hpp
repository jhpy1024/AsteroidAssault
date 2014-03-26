#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>

#include <vector>

#include "Player.hpp"
#include "Texture.hpp"
#include "Sprite.hpp"
#include "SpriteRenderer.hpp"
#include "Asteroid.hpp"

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

	void updatePlayer(Uint32 delta);
	void updateAsteroids(Uint32 delta);

	void createAsteroidsIfNeeded();
	void createAsteroids();
	void removeOutOfBoundAsteroids();

	void handleKeyPress(SDL_Keycode key);
	void handleKeyRelease(SDL_Keycode key);

	std::vector<Sprite> getAsteroidSprites();

public:
	static int WIDTH;
	static int HEIGHT;

private:
	Player m_Player;

	std::vector<Asteroid> m_Asteroids;
	
	Sprite m_Background;
	SpriteRenderer m_SpriteRenderer;

	const Uint32 ASTEROID_CREATION_COUNT;
	const Uint32 ASTEROID_CREATION_DELAY;
	Uint32 m_LastTimeAsteroidsCreated;

	const float RIGHT_BOUND;
	const float LEFT_BOUND;
	const float BOTTOM_BOUND;
};

#endif