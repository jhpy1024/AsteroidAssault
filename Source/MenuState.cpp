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
#include <SDL_mixer.h>

MenuState::MenuState()
	: m_IsSlidingMusic(false)
	, m_IsSlidingSound(false)
{

}

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

	m_MusicSliderBackground.setTextureBounds({ 0.f, 0.f }, { 300.f, 35.f });
	m_MusicSliderBackground.setPosition({ Game::WIDTH / 2.f, Game::HEIGHT * 0.15f });
	auto musicSliderX = (AudioManager::getInstance().getMusicVolume() * 300) / 128 + (m_MusicSliderBackground.getPosition().x - m_MusicSliderBackground.getSize().x / 2.f);
	m_MusicSlider.setTextureBounds({ 300.f, 0.f }, { 30.f, 35.f });
	m_MusicSlider.setPosition({ musicSliderX - m_MusicSlider.getSize().x / 2.f, m_MusicSliderBackground.getPosition().y });
	m_MusicSliderRect.position = m_MusicSlider.getPosition();
	m_MusicSliderRect.width = m_MusicSlider.getSize().x;
	m_MusicSliderRect.height = m_MusicSlider.getSize().y;

	m_SoundSliderBackground.setTextureBounds({ 0.f, 35.f }, { 300.f, 35.f });
	m_SoundSliderBackground.setPosition({ Game::WIDTH / 2.f, Game::HEIGHT * 0.05f });
	auto soundSliderX = (AudioManager::getInstance().getSoundVolume() * 300) / 128 + (m_SoundSliderBackground.getPosition().x - m_SoundSliderBackground.getSize().x / 2.f);
	m_SoundSlider.setTextureBounds({ 300.f, 0.f }, { 30.f, 35.f });
	m_SoundSlider.setPosition({ soundSliderX - m_SoundSlider.getSize().x / 2.f, m_SoundSliderBackground.getPosition().y });
	m_SoundSliderRect.position = m_SoundSlider.getPosition();
	m_SoundSliderRect.width = m_SoundSlider.getSize().x;
	m_SoundSliderRect.height = m_SoundSlider.getSize().y;

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
	else if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			m_IsSlidingMusic = false;
			m_IsSlidingSound = false;
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
	else if (Collision::isColliding(m_MouseRect, m_MusicSliderRect))
	{
		m_IsSlidingMusic = true;
	}
	else if (Collision::isColliding(m_MouseRect, m_SoundSliderRect))
	{
		m_IsSlidingSound = true;
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
	
	if (m_IsSlidingMusic)
	{
		updateSlider(m_MusicSlider, m_MusicSliderBackground, m_MusicSliderRect);
		AudioManager::getInstance().setMusicVolume(calculateVolume(m_MusicSlider, m_MusicSliderBackground));
	}
	if (m_IsSlidingSound)
	{
		updateSlider(m_SoundSlider, m_SoundSliderBackground, m_SoundSliderRect);
		AudioManager::getInstance().setSoundVolume(calculateVolume(m_SoundSlider, m_SoundSliderBackground));
	}

	m_ParticleSys.update(delta);
}

int MenuState::calculateVolume(Sprite& slider, Sprite& sliderBackground)
{
	auto sliderLeft = slider.getPosition().x - slider.getSize().x / 2.f;
	auto backgroundLeft = sliderBackground.getPosition().x - sliderBackground.getSize().x / 2.f;

	std::cout << "Volume = " << ((sliderLeft - backgroundLeft) / 300) * 128 << std::endl;

	return ((sliderLeft - backgroundLeft) / 300) * 128;
}

void MenuState::updateSlider(Sprite& slider, Sprite& sliderBackground, RectangleShape& sliderRect)
{
	slider.setPosition({ Mouse::getX(), slider.getPosition().y });
	sliderRect.position = slider.getPosition();

	auto sliderLeft = slider.getPosition().x - (slider.getSize().x / 2.f);
	auto sliderRight = slider.getPosition().x + (slider.getSize().x / 2.f);
	auto sliderBackgroundLeft = sliderBackground.getPosition().x - (sliderBackground.getSize().x / 2.f);
	auto sliderBackgroundRight = sliderBackground.getPosition().x + (sliderBackground.getSize().x / 2.f);

	if (sliderLeft < sliderBackgroundLeft)
	{
		slider.setPosition({ sliderBackgroundLeft + (slider.getSize().x / 2.f), slider.getPosition().y });
		sliderRect.position = slider.getPosition();
	}
	else if (sliderRight > sliderBackgroundRight)
	{
		slider.setPosition({ sliderBackgroundRight - (slider.getSize().x / 2.f), slider.getPosition().y });
		sliderRect.position = slider.getPosition();
	}

	
}

void MenuState::render()
{
	glClearColor(0.05f, 0.05f, 0.05f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_ParticleRenderer.render(m_ParticleSys);
	m_SpriteRenderer.render(m_Sprites, TextureManager::getInstance().getTexture("MenuSheet"));
	m_SpriteRenderer.render(m_MusicSliderBackground, TextureManager::getInstance().getTexture("UI"));
	m_SpriteRenderer.render(m_MusicSlider, TextureManager::getInstance().getTexture("UI"));
	m_SpriteRenderer.render(m_SoundSliderBackground, TextureManager::getInstance().getTexture("UI"));
	m_SpriteRenderer.render(m_SoundSlider, TextureManager::getInstance().getTexture("UI"));
}