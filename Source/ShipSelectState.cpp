#include "ShipSelectState.hpp"
#include "TextureManager.hpp"

void ShipSelectState::init()
{
	m_CurrentShip = PlayerShipType::RedPointed;
}

void ShipSelectState::handleEvent(const SDL_Event& event)
{

}

void ShipSelectState::handleKeyPress(SDL_Keycode key)
{
	if (key == SDLK_LEFT || key == SDLK_a)
		previousShip();
	else if (key == SDLK_RIGHT || key == SDLK_d)
		nextShip();
}

void ShipSelectState::previousShip()
{

}

void ShipSelectState::nextShip()
{

}

void ShipSelectState::handleKeyRelease(SDL_Keycode key)
{

}

void ShipSelectState::update(Uint32 delta)
{

}

void ShipSelectState::render()
{
	glClearColor(0.05f, 0.05f, 0.05f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_SpriteRenderer.render(m_Sprites, TextureManager::getInstance().getTexture("ShipSelectSheet"));
}

void ShipSelectState::leftButtonPressed()
{

}