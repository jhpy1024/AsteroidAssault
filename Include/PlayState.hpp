#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "State.hpp"
#include "Player.hpp"
#include "Asteroid.hpp"
#include "Sprite.hpp"
#include "ParticleRenderer.hpp"
#include "SpriteRenderer.hpp"
#include "Laser.hpp"
#include "LaserParticleSystem.hpp"
#include "ExplosionParticleSystem.hpp"
#include "Text.hpp"
#include "TextRenderer.hpp"
#include "Powerup.hpp"

#include <vector>
#include <memory>

class PlayState : public State
{
public:
	PlayState();

	void init() override;

	void handleEvent(const SDL_Event& event) override;
	void handleKeyPress(SDL_Keycode key) override;
	void handleKeyRelease(SDL_Keycode key) override;
	void update(Uint32 delta) override;
	void render() override;

private:
	void setupSprites();

	void checkCollisions();
	void checkLaserAsteroidCollisions();
	void checkPlayerAsteroidCollisions();
	void checkPlayerInBounds();

	template <typename T>
	std::vector<Sprite> getSpritesFromCollection(std::vector<std::shared_ptr<T>>& collection);

	void increaseScore();
	void decreaseLives();

	void updatePlayer(Uint32 delta);
	void updateAsteroids(Uint32 delta);
	void updateLasers(Uint32 delta);
	void updateParticles(Uint32 delta);
	void updatePowerups(Uint32 delta);

	bool isFireDelayOver() const;
	void fireLaser();
	void fireLasersIfNeeded();

	void createAsteroidsIfNeeded();
	void createAsteroids();
	void createSubAsteroids(std::shared_ptr<Asteroid> asteroid);

	void removeLasers();
	void removeOutOfBoundLasers();
	void removeFlaggedLasers();

	void addNewAsteroids();
	void removeAsteroids();
	void removeOutOfBoundAsteroids();
	void removeFlaggedAsteroids();

private:
	Player m_Player;

	std::vector<std::shared_ptr<Asteroid>> m_Asteroids;
	std::vector<std::shared_ptr<Laser>> m_Lasers;
	std::vector<std::shared_ptr<Powerup>> m_Powerups;

	Sprite m_Background;
	SpriteRenderer m_SpriteRenderer;

	ParticleRenderer m_ParticleRenderer;
	std::unique_ptr<ExplosionParticleSystem> m_ExplosionParticleSys;
	std::unique_ptr<LaserParticleSystem> m_LaserParticleSys;

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

	int m_Score;
	Text m_ScoreText;

	int m_Lives;
	Text m_LivesText;

	TextRenderer m_TextRenderer;
};

#include "PlayState.inl"

#endif