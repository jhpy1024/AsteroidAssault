#include "MenuState.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include "Mouse.hpp"
#include "Collision.hpp"
#include "StateManager.hpp"
#include "ShipSelectState.hpp"
#include "AudioManager.hpp"
#include "AboutState.hpp"
#include "ShaderManager.hpp"
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

	m_SoundButton.setTextureBounds({ 0.f, 88.f }, { 64.f, 64.f });
	m_SoundButton.setPosition({ 64.f, 64.f });

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

	m_SoundRect.position = m_SoundButton.getPosition();
	m_SoundRect.width = m_SoundButton.getSize().x;
	m_SoundRect.height = m_SoundButton.getSize().y;

	m_MouseRect.width = m_MouseRect.height = 2.f;

	m_ParticleRenderer.init();
	m_ParticleSys.setPosition({ Game::WIDTH / 2.f, Game::HEIGHT / 2.f });
	m_ParticleSys.setEmissionCount(20);

	AudioManager::getInstance().playMusic("TitleMusic", -1);

	if (AudioManager::getInstance().isAudioEnabled())
		m_SoundButton.setTextureBounds({ 0.f, 88.f }, { 64.f, 64.f });
	else
		m_SoundButton.setTextureBounds({ 64.f, 88.f }, { 64.f, 64.f });
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
	{
		AudioManager::getInstance().playSound("Click");
		StateManager::getInstance().push(std::make_shared<ShipSelectState>());
	}
	else if (Collision::isColliding(m_MouseRect, m_AboutRect))
	{
		AudioManager::getInstance().playSound("Click");
		StateManager::getInstance().push(std::make_shared<AboutState>());
	}
	else if (Collision::isColliding(m_MouseRect, m_SoundRect))
	{
		AudioManager::getInstance().playSound("Click");
		AudioManager::getInstance().toggleAudioEnabled();
		if (AudioManager::getInstance().isAudioEnabled())
			m_SoundButton.setTextureBounds({ 0.f, 88.f }, { 64.f, 64.f });
		else
			m_SoundButton.setTextureBounds({ 64.f, 88.f }, { 64.f, 64.f });
	}
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
	m_SpriteRenderer.render(m_SoundButton, TextureManager::getInstance().getTexture("MenuSheet"));
}