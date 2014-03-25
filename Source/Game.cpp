#include "Game.hpp"
#include "ShaderManager.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

int Game::WIDTH;
int Game::HEIGHT;

Game::Game(int width, int height)
	: m_Player(glm::vec2(width / 2.f, 100.f), PlayerShipType::RedPointed)
	, m_PlayerTexture("Resources/Textures/PlayerSheet.png")
{
	WIDTH = width;
	HEIGHT = height;
}

void Game::init()
{
	loadShaders();
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
	m_Player.update(delta);
}

void Game::render()
{
	m_SpriteRenderer.render(m_Player.getSprite(), m_PlayerTexture);
}

void Game::loadShaders()
{
	ShaderManager::getInstance().addShader("Texture", "Resources/Shaders/texture.vert", "Resources/Shaders/texture.frag");
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