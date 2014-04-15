#include "MenuState.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include "Mouse.hpp"
#include "Collision.hpp"
#include "StateManager.hpp"
#include "PlayState.hpp"
#include "AudioManager.hpp"

#include <iostream>
#include <memory>

void MenuState::init()
{
	m_PlayButton.setTextureBounds({ 0.f, 0.f }, { 200.f, 50.f });
	m_PlayButton.setPosition({ Game::WIDTH / 2.f, Game::HEIGHT / 2.f });

	m_AboutButton.setTextureBounds({ 200.f, 0.f }, { 200.f, 50.f });
	m_AboutButton.setPosition({ Game::WIDTH / 2.f, m_PlayButton.getPosition().y - m_AboutButton.getSize().y * 1.5f });

	m_ExitButton.setTextureBounds({ 400.f, 0.f }, { 200.f, 50.f });
	m_ExitButton.setPosition({ Game::WIDTH / 2.f, m_AboutButton.getPosition().y - m_AboutButton.getSize().y * 1.5f });

	m_Title.setPosition({ Game::WIDTH / 2.f, Game::HEIGHT * 0.8f });
	m_Title.setTextureBounds({ 0.f, 50.f }, { 629.f, 38.f });

	m_Sprites.push_back(m_PlayButton);
	m_Sprites.push_back(m_AboutButton);
	m_Sprites.push_back(m_ExitButton);
	m_Sprites.push_back(m_Title);

	m_PlayRect.position = m_PlayButton.getPosition();
	m_PlayRect.width = m_PlayButton.getSize().x;
	m_PlayRect.height = m_PlayButton.getSize().y;

	m_AboutRect.position = m_AboutButton.getPosition();
	m_AboutRect.width = m_AboutButton.getSize().x;
	m_AboutRect.height = m_AboutButton.getSize().y;

	m_ExitRect.position = m_ExitButton.getPosition();
	m_ExitRect.width = m_ExitButton.getSize().x;
	m_ExitRect.height = m_ExitButton.getSize().y;

	m_MouseRect.width = m_MouseRect.height = 2.f;

	m_ParticleRenderer.init();
	m_ParticleSys.setPosition({ Game::WIDTH / 2.f, Game::HEIGHT / 2.f });
	m_ParticleSys.setEmissionCount(20);

	AudioManager::getInstance().playMusic("TitleMusic", -1);
}

void MenuState::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			leftButtonPressed();
		}
	}
}

void MenuState::leftButtonPressed()
{
	if (Collision::isColliding(m_MouseRect, m_PlayRect))
		StateManager::getInstance().push(std::make_shared<PlayState>());
	else if (Collision::isColliding(m_MouseRect, m_AboutRect))
		std::cout << "About button pressed" << std::endl;
	else if (Collision::isColliding(m_MouseRect, m_ExitRect))
	{
		SDL_Quit();
		exit(0);
	}
}

void MenuState::handleKeyPress(SDL_Keycode key)
{

}

void MenuState::handleKeyRelease(SDL_Keycode key)
{

}

void MenuState::update(Uint32 delta)
{
	m_MouseRect.position = Mouse::getPosition();
	
	m_ParticleSys.update(delta);
}

void MenuState::render()
{
	glClearColor(0.05f, 0.05f, 0.05f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_ParticleRenderer.render(m_ParticleSys);
	m_SpriteRenderer.render(m_Sprites, TextureManager::getInstance().getTexture("MenuSheet"));
}