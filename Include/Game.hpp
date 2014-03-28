#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>

#include <vector>
#include <memory>

#include "Player.hpp"
#include "Texture.hpp"
#include "Sprite.hpp"
#include "SpriteRenderer.hpp"
#include "Asteroid.hpp"
#include "Laser.hpp"

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
	void updateLasers(Uint32 delta);

	bool isFireDelayOver() const;
	void fireLaser();

	void createAsteroidsIfNeeded();
	void createAsteroids();
	void removeOutOfBoundAsteroids();
	void removeOutOfBoundLasers();

	void handleKeyPress(SDL_Keycode key);
	void handleKeyRelease(SDL_Keycode key);

	template <typename T>
	std::vector<Sprite> getSpritesFromCollection(std::vector<std::shared_ptr<T>>& collection)
	{
		std::vector<Sprite> sprites;

		for (auto& element : collection)
			sprites.push_back(element->getSprite());

		return sprites;
	}

public:
	static int WIDTH;
	static int HEIGHT;

private:
	Player m_Player;

	std::vector<std::shared_ptr<Asteroid>> m_Asteroids;
	std::vector<std::shared_ptr<Laser>> m_Lasers;
	
	Sprite m_Background;
	SpriteRenderer m_SpriteRenderer;

	const Uint32 ASTEROID_CREATION_COUNT;
	const Uint32 ASTEROID_CREATION_DELAY;
	Uint32 m_LastTimeAsteroidsCreated;

	Uint32 m_LastTimeFiredLaser;
	const Uint32 LASER_FIRE_DELAY;

	const float RIGHT_BOUND;
	const float LEFT_BOUND;
	const float BOTTOM_BOUND;
	const float TOP_BOUND;
};

#endif