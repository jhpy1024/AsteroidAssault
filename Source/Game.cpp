#include "Game.hpp"
#include "Mouse.hpp"
#include "ShaderManager.hpp"
#include "TextureManager.hpp"
#include "Collision.hpp"
#include "AsteroidFactory.hpp"
#include "AudioManager.hpp"
#include "Random.hpp"
#include "StateManager.hpp"
#include "MenuState.hpp"
#include "ShipSelectState.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <algorithm>
#include <memory>

int Game::WIDTH;
int Game::HEIGHT;

Game::Game(int width, int height)
{
	WIDTH = width;
	HEIGHT = height;
}

void Game::init()
{
	loadShaders();
	loadTextures();
	loadAudio();

	setupDefaultMatrices();

	StateManager::getInstance().push(std::make_shared<ShipSelectState>());
}

void Game::loadAudio()
{
	AudioManager::getInstance().loadSound("Laser", "Resources/Sounds/laser.wav");
	AudioManager::getInstance().loadSound("Explosion", "Resources/Sounds/explosion.wav");
	AudioManager::getInstance().loadMusic("TitleMusic", "Resources/Music/TitleMusic.wav");
	AudioManager::getInstance().loadSound("ShieldUp", "Resources/Sounds/shieldUp.ogg");
	AudioManager::getInstance().loadSound("ShieldDown", "Resources/Sounds/shieldDown.ogg");
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

	StateManager::getInstance().top()->handleEvent(event);
}

void Game::handleKeyPress(SDL_Keycode key)
{
	StateManager::getInstance().top()->handleKeyPress(key);
}

void Game::handleKeyRelease(SDL_Keycode key)
{
	StateManager::getInstance().top()->handleKeyRelease(key);
}

void Game::update(Uint32 delta)
{
	ShaderManager::getInstance().getShader("Texture")->bind();
	ShaderManager::getInstance().getShader("Texture")->setUniform("in_Time", static_cast<float>(SDL_GetTicks()));
	ShaderManager::getInstance().getShader("Particle")->bind();
	ShaderManager::getInstance().getShader("Particle")->setUniform("in_Time", static_cast<float>(SDL_GetTicks()));
	ShaderManager::getInstance().getShader("Color")->bind();
	ShaderManager::getInstance().getShader("Color")->setUniform("in_Time", static_cast<float>(SDL_GetTicks()));

	StateManager::getInstance().top()->update(delta);
}

void Game::render()
{
	StateManager::getInstance().top()->render();
}

void Game::loadTextures()
{
	auto& textureManager = TextureManager::getInstance();

	textureManager.addTexture("Player", "Resources/Textures/PlayerSheet.png");
	textureManager.addTexture("Background", "Resources/Textures/Background.png");
	textureManager.addTexture("Asteroid", "Resources/Textures/AsteroidSheet.png");
	textureManager.addTexture("Laser", "Resources/Textures/LaserSheet.png");
	textureManager.addTexture("Particle", "Resources/Textures/Particle.png");
	textureManager.addTexture("TextSheet", "Resources/Textures/TextSheet.png");
	textureManager.addTexture("MenuSheet", "Resources/Textures/MenuSheet.png");
	textureManager.addTexture("DeadSheet", "Resources/Textures/DeadSheet.png");
	textureManager.addTexture("PowerupSheet", "Resources/Textures/PowerupSheet.png");
	textureManager.addTexture("AboutSheet", "Resources/Textures/AboutSheet.png");
} 

void Game::loadShaders()
{
	ShaderManager::getInstance().addShader("Texture", "Resources/Shaders/texture.vert", "Resources/Shaders/texture.frag");
	ShaderManager::getInstance().addShader("Particle", "Resources/Shaders/particle.vert", "Resources/Shaders/particle.frag");
	ShaderManager::getInstance().addShader("Color", "Resources/Shaders/color.vert", "Resources/Shaders/color.frag");
}

void Game::setupDefaultMatrices()
{
	auto textureShader = ShaderManager::getInstance().getShader("Texture");
	auto particleShader = ShaderManager::getInstance().getShader("Particle");
	auto colorShader = ShaderManager::getInstance().getShader("Color");

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

	colorShader->bind();
	colorShader->setUniform("in_ProjectionMatrix", projectionMatrix);
	colorShader->setUniform("in_ViewMatrix", viewMatrix);
	colorShader->setUniform("in_ModelMatrix", modelMatrix);
}