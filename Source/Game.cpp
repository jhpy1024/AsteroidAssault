#include "Game.hpp"
#include "ShaderManager.hpp"
#include "TextureManager.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

int Game::WIDTH;
int Game::HEIGHT;

Game::Game(int width, int height)
	: m_Player(glm::vec2(width / 2.f, 100.f), PlayerShipType::GreenRectangular)
	, ASTEROID_CREATION_COUNT(5)
	, ASTEROID_CREATION_DELAY(2000)
	, m_LastTimeAsteroidsCreated(0)
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
	createAsteroidsIfNeeded();
}

void Game::render()
{
	auto asteroidSprites = getAsteroidSprites();	

	m_SpriteRenderer.render(m_Background, TextureManager::getInstance().getTexture("Background"));
	m_SpriteRenderer.render(m_Player.getSprite(), TextureManager::getInstance().getTexture("Player"));
	m_SpriteRenderer.render(asteroidSprites, TextureManager::getInstance().getTexture("Asteroid"));
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
		m_Asteroids.push_back(Asteroid());
}

void Game::updatePlayer(Uint32 delta)
{
	m_Player.update(delta);
}

void Game::updateAsteroids(Uint32 delta)
{
	for (auto& asteroid : m_Asteroids)
		asteroid.update(delta);
}

std::vector<Sprite> Game::getAsteroidSprites()
{
	std::vector<Sprite> sprites;

	for (auto& asteroid : m_Asteroids)
		sprites.push_back(asteroid.getSprite());

	return sprites;
}

void Game::loadTextures()
{
	auto& textureManager = TextureManager::getInstance();

	textureManager.addTexture("Player", "Resources/Textures/PlayerSheet.png");
	textureManager.addTexture("Background", "Resources/Textures/Background.png");
	textureManager.addTexture("Asteroid", "Resources/Textures/AsteroidSheet.png");
} 

void Game::loadShaders()
{
	ShaderManager::getInstance().addShader("Texture", "Resources/Shaders/texture.vert", "Resources/Shaders/texture.frag");
}

void Game::setupSprites()
{
	m_Background.setPosition(glm::vec2(WIDTH / 2.f, HEIGHT / 2.f));
	m_Background.setTextureBounds(glm::vec2(0.f), glm::vec2(WIDTH, HEIGHT));

	createAsteroids();
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