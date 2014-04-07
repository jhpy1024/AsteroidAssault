#include "Game.hpp"
#include "Mouse.hpp"
#include "ShaderManager.hpp"
#include "TextureManager.hpp"
#include "Collision.hpp"
#include "AsteroidFactory.hpp"
#include "AudioManager.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <algorithm>

int Game::WIDTH;
int Game::HEIGHT;

Game::Game(int width, int height)
	: m_Player(glm::vec2(width / 2.f, 100.f), PlayerShipType::GreenRectangular)
	, ASTEROID_CREATION_COUNT(5)
	, ASTEROID_CREATION_DELAY(2000)
	, m_LastTimeAsteroidsCreated(0)
	, m_LastTimeFiredLaser(0)
	, LASER_FIRE_DELAY(200)
	, m_IsShooting(false)
	, RIGHT_BOUND(width * 1.1f)
	, LEFT_BOUND(-(RIGHT_BOUND - width))
	, BOTTOM_BOUND(LEFT_BOUND)
	, TOP_BOUND(height)
{
	WIDTH = width;
	HEIGHT = height;
}

void Game::init()
{
	loadShaders();
	loadTextures();
	loadAudio();
	setupSprites();
	setupDefaultMatrices();

	m_TestParticleSystem = std::unique_ptr<TestParticleSystem>(new TestParticleSystem);
	m_TestParticleSystem->setEmissionCount(50);
	m_ParticleRenderer.init();
}

void Game::loadAudio()
{
	AudioManager::getInstance().loadSound("Laser", "Resources/Sounds/laser.wav");
	AudioManager::getInstance().loadSound("Explosion", "Resources/Sounds/explosion.wav");
}

void Game::handleEvent(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		handleKeyPress(event.key.keysym.sym);
		break;
	case SDL_KEYUP:
		handleKeyRelease(event.key.keysym.sym);
	default:
		break;
	}
}

void Game::handleKeyPress(SDL_Keycode key)
{
	if (key == SDLK_LEFT)
		m_Player.moveLeft();
	else if (key == SDLK_RIGHT)
		m_Player.moveRight();

	if (key == SDLK_SPACE)
		m_IsShooting = true;
}

void Game::handleKeyRelease(SDL_Keycode key)
{
	if (key == SDLK_LEFT)
		m_Player.stopMovingLeft();
	else if (key == SDLK_RIGHT)
		m_Player.stopMovingRight();
	
	if (key == SDLK_SPACE)
		m_IsShooting = false;
}

void Game::update(Uint32 delta)
{
	updatePlayer(delta);
	updateAsteroids(delta);
	updateLasers(delta);
	fireLasersIfNeeded();
	createAsteroidsIfNeeded();
	checkCollisions();
	
	removeLasers();
	removeAsteroids();
	addNewAsteroids();

	m_TestParticleSystem->update(delta);
}

void Game::addNewAsteroids()
{
	if (m_AsteroidsToAdd.empty()) return;
	m_Asteroids.insert(m_Asteroids.end(), m_AsteroidsToAdd.begin(), m_AsteroidsToAdd.end());
	m_AsteroidsToAdd.clear();
}

void Game::checkCollisions()
{
	checkLaserAsteroidCollisions();
}

void Game::checkLaserAsteroidCollisions()
{
	for (auto& asteroid : m_Asteroids)
	{
		for (auto& laser : m_Lasers)
		{
			if (Collision::isColliding(laser->getShape(), asteroid->getShape()))
			{
				laser->flagForRemoval();

				auto subAsteroids = AsteroidFactory::createSubAsteroids(*asteroid);
				for (auto& newAsteroid : subAsteroids)
					m_AsteroidsToAdd.push_back(newAsteroid);

				asteroid->flagForRemoval();

				m_TestParticleSystem->setPosition(asteroid->getSprite().getPosition());
				m_TestParticleSystem->emitParticles();

				AudioManager::getInstance().playSound("Explosion");
			}
		}
	}
}

void Game::render()
{
	auto asteroidSprites = getSpritesFromCollection(m_Asteroids);	
	auto laserSprites = getSpritesFromCollection(m_Lasers);

	m_SpriteRenderer.render(m_Background, TextureManager::getInstance().getTexture("Background"));
	m_SpriteRenderer.render(m_Player.getSprite(), TextureManager::getInstance().getTexture("Player"));
	m_SpriteRenderer.render(asteroidSprites, TextureManager::getInstance().getTexture("Asteroid"));	
	m_SpriteRenderer.render(laserSprites, TextureManager::getInstance().getTexture("Laser"));

	m_ParticleRenderer.render(*m_TestParticleSystem);
}

void Game::fireLasersIfNeeded()
{
	if (m_IsShooting)
		fireLaser();
}

void Game::removeLasers()
{
	removeOutOfBoundLasers();
	removeFlaggedLasers();
}

void Game::removeAsteroids()
{
	removeOutOfBoundAsteroids();
	removeFlaggedAsteroids();
}

void Game::removeFlaggedAsteroids()
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

void Game::removeFlaggedLasers()
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

void Game::removeOutOfBoundLasers()
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

void Game::removeOutOfBoundAsteroids()
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

void Game::createAsteroidsIfNeeded()
{
	auto currentTime = SDL_GetTicks();
	auto elapsedTime = currentTime - m_LastTimeAsteroidsCreated;

	if (elapsedTime >= ASTEROID_CREATION_DELAY)
	{
		createAsteroids();
		m_LastTimeAsteroidsCreated = currentTime;
	}
}

void Game::createAsteroids()
{
	for (int i = 0; i < ASTEROID_CREATION_COUNT; ++i)
		m_Asteroids.push_back(std::make_shared<Asteroid>());
}

void Game::fireLaser()
{
	if (isFireDelayOver())
	{
		auto position = m_Player.getSprite().getPosition();
		auto rotation = m_Player.getSprite().getRotationDegs();

		m_Lasers.push_back(std::make_shared<Laser>(position, rotation, LaserType::Red));

		AudioManager::getInstance().playSound("Laser");

		m_LastTimeFiredLaser = SDL_GetTicks();
	}
}

bool Game::isFireDelayOver() const
{
	auto currentTime = SDL_GetTicks();
	auto elapsedTime = currentTime - m_LastTimeFiredLaser;

	return elapsedTime >= LASER_FIRE_DELAY;
}

void Game::updateLasers(Uint32 delta)
{
	for (auto& laser : m_Lasers)
		laser->update(delta);
}

void Game::updatePlayer(Uint32 delta)
{
	m_Player.update(delta);
}

void Game::updateAsteroids(Uint32 delta)
{
	for (auto& asteroid : m_Asteroids)
		asteroid->update(delta);
}

void Game::loadTextures()
{
	auto& textureManager = TextureManager::getInstance();

	textureManager.addTexture("Player", "Resources/Textures/PlayerSheet.png");
	textureManager.addTexture("Background", "Resources/Textures/Background.png");
	textureManager.addTexture("Asteroid", "Resources/Textures/AsteroidSheet.png");
	textureManager.addTexture("Laser", "Resources/Textures/LaserSheet.png");
	textureManager.addTexture("Particle", "Resources/Textures/Particle.png");
} 

void Game::loadShaders()
{
	ShaderManager::getInstance().addShader("Texture", "Resources/Shaders/texture.vert", "Resources/Shaders/texture.frag");
	ShaderManager::getInstance().addShader("Particle", "Resources/Shaders/particle.vert", "Resources/Shaders/particle.frag");
}

void Game::setupSprites()
{
	m_Background.setPosition(glm::vec2(WIDTH / 2.f, HEIGHT / 2.f));
	m_Background.setTextureBounds(glm::vec2(0.f), glm::vec2(WIDTH, HEIGHT));
}

void Game::setupDefaultMatrices()
{
	auto textureShader = ShaderManager::getInstance().getShader("Texture");
	auto particleShader = ShaderManager::getInstance().getShader("Particle");
	auto projectionMatrix = glm::ortho(0.f, static_cast<float>(WIDTH), 0.f, static_cast<float>(HEIGHT));
	auto viewMatrix = glm::mat4(1.f);
	auto modelMatrix = glm::mat4(1.f);

	textureShader->bind();
	textureShader->setUniform("in_ProjectionMatrix", projectionMatrix);
	textureShader->setUniform("in_ViewMatrix", viewMatrix);
	textureShader->setUniform("in_ModelMatrix", modelMatrix);
	particleShader->bind();
	particleShader->setUniform("in_ProjectionMatrix", projectionMatrix);
	particleShader->setUniform("in_ViewMatrix", viewMatrix);
	particleShader->setUniform("in_ModelMatrix", modelMatrix);
}