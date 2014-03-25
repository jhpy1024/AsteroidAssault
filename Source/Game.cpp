#include "Game.hpp"
#include "ShaderManager.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
	setupDefaultMatrices();
}

void Game::handleEvent(const SDL_Event& event)
{

}

void Game::update(Uint32 delta)
{

}

void Game::render()
{

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