#include "Game.hpp"
#include "Mouse.hpp"
#include "ShaderManager.hpp"
#include "TextureManager.hpp"
#include "Collision.hpp"
#include "AsteroidFactory.hpp"
#include "AudioManager.hpp"
#include "Random.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <algorithm>

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
	
}

void Game::handleKeyRelease(SDL_Keycode key)
{
	
}

void Game::update(Uint32 delta)
{

}

void Game::render()
{

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
} 

void Game::loadShaders()
{
	ShaderManager::getInstance().addShader("Texture", "Resources/Shaders/texture.vert", "Resources/Shaders/texture.frag");
	ShaderManager::getInstance().addShader("Particle", "Resources/Shaders/particle.vert", "Resources/Shaders/particle.frag");
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