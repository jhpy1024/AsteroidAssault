#include "PlayState.hpp"
#include "AsteroidFactory.hpp"
#include "Collision.hpp"
#include "Random.hpp"
#include "AudioManager.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include "StateManager.hpp"
#include "DeadState.hpp"
#include "ShaderManager.hpp"
#include "MathUtils.hpp"
#include "Mouse.hpp"

#include <iostream>

PlayState::PlayState()
	: m_Player(glm::vec2(Game::WIDTH / 2.f, 100.f), PlayerShipType::GreenRectangular)
	, ASTEROID_CREATION_COUNT(5)
	, ASTEROID_CREATION_DELAY(2000)
	, m_LastTimeAsteroidsCreated(0)
	, m_LastTimeFiredLaser(0)
	, LASER_FIRE_DELAY(200)
	, m_IsShooting(false)
	, RIGHT_BOUND(Game::WIDTH * 1.1f)
	, LEFT_BOUND(-(RIGHT_BOUND - Game::WIDTH))
	, BOTTOM_BOUND(LEFT_BOUND)
	, TOP_BOUND(Game::HEIGHT)
	, m_Score(0)
	, m_ScoreText("Score: 0", { Game::WIDTH * 0.05f, Game::HEIGHT * 0.05f }, { 0.f, 1.f, 0.f, 1.f })
	, m_Lives(3)
	, m_LivesText("Lives: " + std::to_string(m_Lives), { Game::WIDTH * 0.78f, Game::HEIGHT * 0.05f }, { 0.f, 1.f, 0.f, 1.f })
	, m_CurrentPowerup(PowerupType::Last)
	, m_LastTimePowerupCreated(0)
	, m_TimeCollectedPowerup(0)
	, POWERUP_CREATION_DELAY(10000)
	, TIME_TRIPLE_LASERS_ACTIVE(5000)
	, TIME_SHIELD_ACTIVE(8000)
{
	
}

void PlayState::init()
{
	setupSprites();

	m_ExplosionParticleSys = std::unique_ptr<ExplosionParticleSystem>(new ExplosionParticleSystem);
	m_ExplosionParticleSys->setEmissionCount(70);
	m_LaserParticleSys = std::unique_ptr<LaserParticleSystem>(new LaserParticleSystem);
	m_LaserParticleSys->setEmissionCount(5);
	m_ParticleRenderer.init();

	m_TextRenderer.init();
	m_ScoreText.setCharacterSize({ 15.f, 15.f });
	m_ScoreText.setPadding({ 2.f, 0.f });
	m_LivesText.setCharacterSize({ 15.f, 15.f });
	m_LivesText.setPadding({ 2.f, 0.f });

	m_Shield.radius = 64.f;
	m_Shield.color = { 0.f, 1.f, 1.f, 1.f };
	m_ShapeRenderer.init();

	m_LightningRenderer.init();

	for (int i = 0; i < 5; ++i)
	{
		m_Lightning.push_back(std::make_shared<Lightning>(glm::vec2(Game::WIDTH / 2.f, Game::HEIGHT)));
	}
}

void PlayState::handleEvent(const SDL_Event& event)
{

}

void PlayState::handleKeyPress(SDL_Keycode key)
{
	if (key == SDLK_LEFT)
		m_Player.moveLeft();
	else if (key == SDLK_RIGHT)
		m_Player.moveRight();

	if (key == SDLK_SPACE)
		m_IsShooting = true;
	
	if (key == SDLK_ESCAPE)
		StateManager::getInstance().pop();
}

void PlayState::handleKeyRelease(SDL_Keycode key)
{
	if (key == SDLK_LEFT)
		m_Player.stopMovingLeft();
	else if (key == SDLK_RIGHT)
		m_Player.stopMovingRight();

	if (key == SDLK_SPACE)
	{
		m_IsShooting = false;
		ShaderManager::getInstance().disableScrenShake();
	}
}

void PlayState::update(Uint32 delta)
{
	updatePlayer(delta);
	updateAsteroids(delta);
	updateLasers(delta);
	updateParticles(delta);
	updatePowerups(delta);
	updateShield(delta);

	fireLasersIfNeeded();
	removeLasers();

	createAsteroidsIfNeeded();
	removeAsteroids();
	addNewAsteroids();

	createPowerupsIfNeeded();
	removePowerups();

	checkCollisions();

	checkIfPowerupOver();
	
	m_ScoreText.setString("Score: " + std::to_string(m_Score));

	for (auto& strike : m_Lightning)
	{
		strike->setTargetPosition(m_Player.getSprite().getPosition());
		strike->update(delta);
	}
}

void PlayState::updateShield(Uint32 delta)
{
	if (m_CurrentPowerup != PowerupType::Shield)
	{
		m_Shield.radius = 0.f;
		return;
	}

	if (m_Shield.radius == 0.f) m_Shield.radius = 64.f;

	static int direction = 1;

	if (m_Shield.radius >= 96.f)
		direction = -1;
	if (m_Shield.radius <= 64.f)
		direction = 1;

	m_Shield.radius += 0.05f * direction * delta;
	m_Shield.color.w = MathUtils::smoothStep(m_Shield.radius, 64.f * 0.75f, 96.f);
	m_Shield.position = m_Player.getSprite().getPosition();
}

void PlayState::checkIfPowerupOver()
{
	switch (m_CurrentPowerup)
	{
	case PowerupType::Laser:
		if (SDL_GetTicks() - m_TimeCollectedPowerup >= TIME_TRIPLE_LASERS_ACTIVE)
			m_CurrentPowerup = PowerupType::Last;
		break;
	case PowerupType::Shield:
		if (SDL_GetTicks() - m_TimeCollectedPowerup >= TIME_SHIELD_ACTIVE)
			m_CurrentPowerup = PowerupType::Last;
		break;
	default:
		break;
	}
}

void PlayState::createPowerupsIfNeeded()
{
	if (SDL_GetTicks() - m_LastTimePowerupCreated >= POWERUP_CREATION_DELAY)
	{
		auto position = glm::vec2(Random::genFloat(0.f, Game::WIDTH), Game::HEIGHT * 1.2f);
		auto velocity = glm::vec2(0.f, -0.10f);
		auto powerupType = static_cast<PowerupType::Type>(Random::genInt(0, PowerupType::Last - 1));

		m_Powerups.push_back(std::make_shared<Powerup>(position, velocity, powerupType));

		m_LastTimePowerupCreated = SDL_GetTicks();
	}
}

void PlayState::updatePowerups(Uint32 delta)
{
	for (auto& powerup : m_Powerups)
		powerup->update(delta);
}

void PlayState::updateParticles(Uint32 delta)
{
	m_ExplosionParticleSys->update(delta);
	m_LaserParticleSys->update(delta);
}

void PlayState::addNewAsteroids()
{
	if (m_AsteroidsToAdd.empty()) return;
	m_Asteroids.insert(m_Asteroids.end(), m_AsteroidsToAdd.begin(), m_AsteroidsToAdd.end());
	m_AsteroidsToAdd.clear();
}

void PlayState::checkCollisions()
{
	checkLaserAsteroidCollisions();
	checkPlayerAsteroidCollisions();
	checkPlayerPowerupCollisions();
	checkPlayerInBounds();
}

void PlayState::checkPlayerPowerupCollisions()
{
	for (auto& powerup : m_Powerups)
	{
		if (Collision::isColliding(m_Player.getShape(), powerup->getShape()))
		{
			// NOT USED YET.
			m_Player.collectedPowerup(powerup->getType());
			m_CurrentPowerup = powerup->getType();
			powerup->flagForRemoval();

			collectedPowerup();

			m_TimeCollectedPowerup = SDL_GetTicks();
		}
	}
}

void PlayState::collectedPowerup()
{
	switch (m_CurrentPowerup)
	{
	case PowerupType::Health:
		++m_Lives;
		m_LivesText.setString("Lives: " + std::to_string(m_Lives));
		m_LivesText.setColor({ Random::genFloat(0.3f, 1.f), Random::genFloat(0.3f, 1.f), Random::genFloat(0.3f, 1.f), 1.f });
		break;
	default:
		break;
	}
}

void PlayState::checkPlayerInBounds()
{
	auto pos = m_Player.getSprite().getPosition();
	auto size = m_Player.getSprite().getSize();

	if (pos.x - size.x / 2.f < 0.f)
		m_Player.getSprite().setPosition({ 0.f + size.x / 2.f, pos.y });
	else if (pos.x + size.x / 2.f > Game::WIDTH)
		m_Player.getSprite().setPosition({ Game::WIDTH - size.x / 2.f, pos.y });
}

void PlayState::checkPlayerAsteroidCollisions()
{
	for (auto& asteroid : m_Asteroids)
	{
		if (m_CurrentPowerup == PowerupType::Shield)
		{
			if (Collision::isColliding(m_Shield, asteroid->getShape()))
			{
				asteroid->reverseDirection();
				continue;
			}
		}

		if (Collision::isColliding(m_Player.getShape(), asteroid->getShape()))
		{
			asteroid->flagForRemoval();
			decreaseLives();
		}
	}
}

void PlayState::decreaseLives()
{
	if (m_Lives > 1)
	{
		--m_Lives;
		m_LivesText.setString("Lives: " + std::to_string(m_Lives));
		m_LivesText.setColor({ Random::genFloat(0.3f, 1.f), Random::genFloat(0.3f, 1.f), Random::genFloat(0.3f, 1.f), 1.f });
	}
	else
	{
		ShaderManager::getInstance().disableScrenShake();
		StateManager::getInstance().push(std::make_shared<DeadState>(m_Score));
	}
}

void PlayState::checkLaserAsteroidCollisions()
{
	for (auto& asteroid : m_Asteroids)
	{
		for (auto& laser : m_Lasers)
		{
			if (Collision::isColliding(laser->getShape(), asteroid->getShape()))
			{
				createSubAsteroids(asteroid);

				laser->flagForRemoval();
				asteroid->flagForRemoval();

				m_ExplosionParticleSys->setPosition(asteroid->getSprite().getPosition());
				m_ExplosionParticleSys->emitParticles();

				AudioManager::getInstance().playSound("Explosion");

				increaseScore();
			}
		}
	}
}

void PlayState::createSubAsteroids(std::shared_ptr<Asteroid> asteroid)
{
	auto subAsteroids = AsteroidFactory::createSubAsteroids(*asteroid);
	for (auto& newAsteroid : subAsteroids)
		m_AsteroidsToAdd.push_back(newAsteroid);
}

void PlayState::render()
{
	auto asteroidSprites = getSpritesFromCollection(m_Asteroids);
	auto laserSprites = getSpritesFromCollection(m_Lasers);
	auto powerupSprites = getSpritesFromCollection(m_Powerups);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_SpriteRenderer.render(m_Background, TextureManager::getInstance().getTexture("Background"));
	m_ShapeRenderer.render(std::make_shared<CircleShape>(m_Shield));
	m_SpriteRenderer.render(m_Player.getSprite(), TextureManager::getInstance().getTexture("Player"));
	m_SpriteRenderer.render(asteroidSprites, TextureManager::getInstance().getTexture("Asteroid"));
	m_SpriteRenderer.render(powerupSprites, TextureManager::getInstance().getTexture("PowerupSheet"));
	m_SpriteRenderer.render(laserSprites, TextureManager::getInstance().getTexture("Laser"));

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	m_ParticleRenderer.render(*m_ExplosionParticleSys);
	m_ParticleRenderer.render(*m_LaserParticleSys);
	m_LightningRenderer.render(m_Lightning);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_TextRenderer.render(m_ScoreText, TextureManager::getInstance().getTexture("TextSheet"));
	m_TextRenderer.render(m_LivesText, TextureManager::getInstance().getTexture("TextSheet"));
}

void PlayState::increaseScore()
{
	m_Score += 100;
	m_ScoreText.setColor({ Random::genFloat(0.3f, 1.f), Random::genFloat(0.3f, 1.f), Random::genFloat(0.3f, 1.f), 1.f });
}

void PlayState::fireLasersIfNeeded()
{
	if (m_IsShooting)
		fireLaser();
}

void PlayState::removeLasers()
{
	removeOutOfBoundLasers();
	removeFlaggedLasers();
}

void PlayState::removeAsteroids()
{
	removeOutOfBoundAsteroids();
	removeFlaggedAsteroids();
}

void PlayState::removePowerups()
{
	if (m_Powerups.empty()) return;

	auto itr = m_Powerups.begin();

	while (itr != m_Powerups.end())
	{
		if ((*itr)->shouldRemove())
			itr = m_Powerups.erase(itr);
		else
			++itr;
	}
}

void PlayState::removeFlaggedAsteroids()
{
	if (m_Asteroids.empty()) return;

	auto itr = m_Asteroids.begin();

	while (itr != m_Asteroids.end())
	{
		if ((*itr)->shouldRemove())
			itr = m_Asteroids.erase(itr);
		else
			++itr;
	}
}

void PlayState::removeFlaggedLasers()
{
	if (m_Lasers.empty()) return;

	auto itr = m_Lasers.begin();

	while (itr != m_Lasers.end())
	{
		if ((*itr)->shouldRemove())
			itr = m_Lasers.erase(itr);
		else
			++itr;
	}
}

void PlayState::removeOutOfBoundLasers()
{
	if (m_Lasers.empty()) return;

	auto itr = m_Lasers.begin();

	while (itr != m_Lasers.end())
	{
		auto position = (*itr)->getSprite().getPosition();

		if ((position.x <= LEFT_BOUND) || (position.x >= RIGHT_BOUND) || (position.y <= BOTTOM_BOUND) || (position.y >= TOP_BOUND))
			itr = m_Lasers.erase(itr);
		else
			++itr;
	}
}

void PlayState::removeOutOfBoundAsteroids()
{
	if (m_Asteroids.empty()) return;

	auto itr = m_Asteroids.begin();

	while (itr != m_Asteroids.end())
	{
		auto position = (*itr)->getSprite().getPosition();

		if ((position.x <= LEFT_BOUND) || (position.x >= RIGHT_BOUND) || (position.y <= BOTTOM_BOUND))
			itr = m_Asteroids.erase(itr);
		else
			++itr;
	}
}

void PlayState::createAsteroidsIfNeeded()
{
	auto currentTime = SDL_GetTicks();
	auto elapsedTime = currentTime - m_LastTimeAsteroidsCreated;

	if (elapsedTime >= ASTEROID_CREATION_DELAY)
	{
		createAsteroids();
		m_LastTimeAsteroidsCreated = currentTime;
	}
}

void PlayState::createAsteroids()
{
	for (int i = 0; i < ASTEROID_CREATION_COUNT; ++i)
		m_Asteroids.push_back(std::make_shared<Asteroid>());
}

void PlayState::fireLaser()
{
	if (isFireDelayOver())
	{
		auto position = m_Player.getSprite().getPosition();
		auto size = m_Player.getSprite().getSize();
		auto rotation = m_Player.getSprite().getRotationDegs();

		if (m_CurrentPowerup == PowerupType::Laser)
		{
			m_Lasers.push_back(std::make_shared<Laser>(glm::vec2(position.x - size.x / 2.f, position.y), rotation, LaserType::Red));
			m_Lasers.push_back(std::make_shared<Laser>(glm::vec2(position.x, position.y), rotation, LaserType::Red));
			m_Lasers.push_back(std::make_shared<Laser>(glm::vec2(position.x + size.x / 2.f, position.y), rotation, LaserType::Red));
		}
		else
		{
			m_Lasers.push_back(std::make_shared<Laser>(position, rotation, LaserType::Red));
		}

		AudioManager::getInstance().playSound("Laser");
		ShaderManager::getInstance().enableScreenShake(m_CurrentPowerup == PowerupType::Laser ? 8.f : 3.f);

		m_LastTimeFiredLaser = SDL_GetTicks();
	}
}

bool PlayState::isFireDelayOver() const
{
	auto currentTime = SDL_GetTicks();
	auto elapsedTime = currentTime - m_LastTimeFiredLaser;

	return elapsedTime >= LASER_FIRE_DELAY;
}

void PlayState::updateLasers(Uint32 delta)
{
	for (auto& laser : m_Lasers)
	{
		laser->update(delta);
		m_LaserParticleSys->setPosition(laser->getSprite().getPosition());
		m_LaserParticleSys->emitParticles();
	}
}

void PlayState::updatePlayer(Uint32 delta)
{
	m_Player.update(delta);
}

void PlayState::updateAsteroids(Uint32 delta)
{
	for (auto& asteroid : m_Asteroids)
	{
		asteroid->update(delta);
	}
}

void PlayState::setupSprites()
{
	m_Background.setPosition(glm::vec2(Game::WIDTH / 2.f, Game::HEIGHT / 2.f));
	m_Background.setTextureBounds(glm::vec2(0.f), glm::vec2(Game::WIDTH, Game::HEIGHT));
}