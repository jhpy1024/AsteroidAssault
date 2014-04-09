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
#include "ParticleRenderer.hpp"
#include "TestParticleSystem.hpp"
#include "TextRenderer.hpp"
#include "Text.hpp"

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
	void setupSprites();
	void setupDefaultMatrices();

	void updatePlayer(Uint32 delta);
	void updateAsteroids(Uint32 delta);
	void updateLasers(Uint32 delta);

	bool isFireDelayOver() const;
	void fireLaser();
	void fireLasersIfNeeded();

	void createAsteroidsIfNeeded();
	void createAsteroids();

	void removeLasers();
	void removeOutOfBoundLasers();
	void removeFlaggedLasers();

	void addNewAsteroids();
	void removeAsteroids();
	void removeOutOfBoundAsteroids();
	void removeFlaggedAsteroids();

	void handleKeyPress(SDL_Keycode key);
	void handleKeyRelease(SDL_Keycode key);

	void checkCollisions();
	void checkLaserAsteroidCollisions();

	template <typename T>
	std::vector<Sprite> getSpritesFromCollection(std::vector<std::shared_ptr<T>>& collection);

public:
	static int WIDTH;
	static int HEIGHT;

private:
	Player m_Player;

	std::vector<std::shared_ptr<Asteroid>> m_Asteroids;
	std::vector<std::shared_ptr<Laser>> m_Lasers;
	
	Sprite m_Background;
	SpriteRenderer m_SpriteRenderer;

	ParticleRenderer m_ParticleRenderer;
	std::unique_ptr<TestParticleSystem> m_TestParticleSystem;

	const Uint32 ASTEROID_CREATION_COUNT;
	const Uint32 ASTEROID_CREATION_DELAY;
	Uint32 m_LastTimeAsteroidsCreated;

	Uint32 m_LastTimeFiredLaser;
	const Uint32 LASER_FIRE_DELAY;
	bool m_IsShooting;

	const float RIGHT_BOUND;
	const float LEFT_BOUND;
	const float BOTTOM_BOUND;
	const float TOP_BOUND;

	std::vector<std::shared_ptr<Asteroid>> m_AsteroidsToAdd;

	Text m_TestText;
	TextRenderer m_TextRenderer;
};

#include "Game.inl"

#endif