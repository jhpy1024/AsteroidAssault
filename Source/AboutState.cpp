#include "AboutState.hpp"
#include "Game.hpp"
#include "Mouse.hpp"
#include "TextureManager.hpp"
#include "Collision.hpp"
#include "StateManager.hpp"
#include "AudioManager.hpp"

AboutState::AboutState()
	: m_ParticleSys({ 0.f, 1.f, 0.f })	
{

}

void AboutState::init()
{
	m_ParticleRenderer.init();
	m_ParticleSys.setPosition({ Game::WIDTH / 2.f, Game::HEIGHT / 2.f });
	m_ParticleSys.setEmissionCount(20);

	m_Title.setPosition({ Game::WIDTH / 2.f, Game::HEIGHT * 0.8f });
	m_Title.setTextureBounds({ 0.f, 50.f }, { 629.f, 38.f });

	m_BackBtn.setPosition({ Game::WIDTH * 0.15f, Game::HEIGHT * 0.05f });
	m_BackBtn.setTextureBounds({ 0.f, 0.f }, { 200.f, 50.f });

	m_Sprites.push_back(m_BackBtn);
	m_Sprites.push_back(m_Title);

	m_ProgrammerText.setString("Programmer: Jake Horsfield");
	m_ArtText.setString("Art: opengameart.org");
	m_SoundsText.setString("Sound: freesound.org");

	m_ForText.setString("For Zephilinox, Happy Birthday!    (on the 27th :3)");
	m_ForText.setVerticalPadding(2.f);
	m_ForText.enableCharWrap();
	m_ForText.setCharWrapLimit(31);

	m_TextRenderer.init();
	m_Text.push_back(m_ProgrammerText);
	m_Text.push_back(m_ArtText);
	m_Text.push_back(m_SoundsText);
	m_Text.push_back(m_ForText);

	for (int i = 0; i < m_Text.size(); ++i)
	{
		m_Text[i].setColor({ 0.f, 1.f, 1.f, 1.f });
		m_Text[i].setCharacterSize({ 13.f, 13.f });
		m_Text[i].setHorizontalPadding(2.f);
		m_Text[i].setPosition({ Game::WIDTH * 0.08f, (Game::HEIGHT / 2.f) - 20.f * i });
	}

	m_BackRect.position = m_BackBtn.getPosition();
	m_BackRect.width = m_BackBtn.getSize().x;
	m_BackRect.height = m_BackBtn.getSize().y;

	m_MouseRect.width = m_MouseRect.height = 2.f;
}

void AboutState::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
			leftButtonPressed();
	}
}

void AboutState::leftButtonPressed()
{
	if (Collision::isColliding(m_MouseRect, m_BackRect))
	{
		AudioManager::getInstance().playSound("Click");
		StateManager::getInstance().pop();
	}
}

void AboutState::handleKeyPress(SDL_Keycode key)
{

}

void AboutState::handleKeyRelease(SDL_Keycode key)
{

}

void AboutState::update(Uint32 delta)
{
	m_MouseRect.position = Mouse::getPosition();

	m_ParticleSys.update(delta);
}

void AboutState::render()
{
	glClearColor(0.05f, 0.05f, 0.05f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_ParticleRenderer.render(m_ParticleSys);
	m_SpriteRenderer.render(m_Sprites, TextureManager::getInstance().getTexture("AboutSheet"));
	m_TextRenderer.render(m_Text, TextureManager::getInstance().getTexture("TextSheet"));
}