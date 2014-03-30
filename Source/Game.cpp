#include "Game.hpp"
#include "ShaderManager.hpp"
#include "TextureManager.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "RectangleShape.hpp"
#include "Collision.hpp"

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
	setupSprites();
	setupDefaultMatrices();

	RectangleShape r1, r2;
	r1.width = r2.width = 100.f;
	r1.height = r2.height = 10.f;
	r1.position = glm::vec2(0.f, 0.f);
	r2.position = glm::vec2(100.f, 0.f);

	std::cout << Collision::isColliding(r1, r2) << std::endl;
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
		fireLaser();
}

void Game::handleKeyRelease(SDL_Keycode key)
{
	if (key == SDLK_LEFT || key == SDLK_RIGHT)
		m_Player.stopMoving();
}

void Game::update(Uint32 delta)
{
	updatePlayer(delta);
	updateAsteroids(delta);
	updateLasers(delta);
	createAsteroidsIfNeeded();
	removeOutOfBoundAsteroids();
	removeOutOfBoundLasers();
}

void Game::render()
{
	auto asteroidSprites = getSpritesFromCollection(m_Asteroids);	
	auto laserSprites = getSpritesFromCollection(m_Lasers);

	m_SpriteRenderer.render(m_Background, TextureManager::getInstance().getTexture("Background"));
	m_SpriteRenderer.render(m_Player.getSprite(), TextureManager::getInstance().getTexture("Player"));
	m_SpriteRenderer.render(asteroidSprites, TextureManager::getInstance().getTexture("Asteroid"));	
	m_SpriteRenderer.render(laserSprites, TextureManager::getInstance().getTexture("Laser"));
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
} 

void Game::loadShaders()
{
	ShaderManager::getInstance().addShader("Texture", "Resources/Shaders/texture.vert", "Resources/Shaders/texture.frag");
}

void Game::setupSprites()
{
	m_Background.setPosition(glm::vec2(WIDTH / 2.f, HEIGHT / 2.f));
	m_Background.setTextureBounds(glm::vec2(0.f), glm::vec2(WIDTH, HEIGHT));
}

void Game::setupDefaultMatrices()
{
	auto textureShader = ShaderManager::getInstance().getShader("Texture");
	auto projectionMatrix = glm::ortho(0.f, static_cast<float>(WIDTH), 0.f, static_cast<float>(HEIGHT));
	auto viewMatrix = glm::mat4(1.f);
	auto modelMatrix = glm::mat4(1.f);

	textureShader->bind();
	textureShader->setUniform("in_ProjectionMatrix", projectionMatrix);
	textureShader->setUniform("in_ViewMatrix", viewMatrix);
	textureShader->setUniform("in_ModelMatrix", modelMatrix);
}