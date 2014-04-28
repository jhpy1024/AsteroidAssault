#include "DeadState.hpp"
#include "Game.hpp"
#include "Mouse.hpp"
#include "TextureManager.hpp"
#include "Collision.hpp"
#include "MenuState.hpp"
#include "StateManager.hpp"
#include "ShaderManager.hpp"
#include "AudioManager.hpp"

#include <fstream>
#include <string>

DeadState::DeadState(int score)
	: m_Score(score)
	, m_ParticleSys({ 1.f, 0.f, 0.f })
{
	auto highestScore = readHighestScore();
	if (m_Score > highestScore)
		writeHighestScore();
}

void DeadState::writeHighestScore()
{
	std::ofstream file(".highestScore", std::ios::trunc);
	if (file.is_open())
		file << m_Score;

	file.close();
}

int DeadState::readHighestScore() const
{
	std::string line;
	std::ifstream file(".highestScore");
	
	if (file.is_open())
		std::getline(file, line);

	file.close();

	if (line.empty())
		return 0;
	else
		return std::stoi(line);
}

void DeadState::init()
{
	m_RetryButton.setTextureBounds({ 0.f, 0.f }, { 200.f, 50.f });
	m_RetryButton.setPosition({ Game::WIDTH / 2.f, Game::HEIGHT / 2.f });

	m_ExitButton.setTextureBounds({ 200.f, 0.f }, { 200.f, 50.f });
	m_ExitButton.setPosition({ Game::WIDTH / 2.f, m_RetryButton.getPosition().y - m_RetryButton.getSize().y * 1.5f });

	m_Title.setPosition({ Game::WIDTH / 2.f, Game::HEIGHT * 0.8f });
	m_Title.setTextureBounds({ 0.f, 50.f }, { 361.f, 39.f });

	m_Sprites.push_back(m_RetryButton);
	m_Sprites.push_back(m_ExitButton);
	m_Sprites.push_back(m_Title);

	m_RetryRect.position = m_RetryButton.getPosition();
	m_RetryRect.width = m_RetryButton.getSize().x;
	m_RetryRect.height = m_RetryButton.getSize().y;

	m_ExitRect.position = m_ExitButton.getPosition();
	m_ExitRect.width = m_ExitButton.getSize().x;
	m_ExitRect.height = m_ExitButton.getSize().y;

	m_MouseRect.width = m_MouseRect.height = 2.f;

	m_ScoreText.setHorizontalPadding(2.f);
	m_ScoreText.setCharacterSize({ 20.f, 20.f });
	m_ScoreText.setString("Score: " + std::to_string(m_Score));
	m_ScoreText.setPosition({ m_Title.getPosition().x - (m_ScoreText.getStringLength() * 22.f) / 2.f, m_Title.getPosition().y - m_Title.getSize().y });
	m_ScoreText.setColor({ 0.f, 1.f, 1.f, 1.f });

	m_HighestScoreText.setPosition({ m_ScoreText.getPosition().x, m_ScoreText.getPosition().y - m_ScoreText.getCharacterSize().y * 1.5f });
	m_HighestScoreText.setHorizontalPadding(2.f);
	m_HighestScoreText.setString("Highest Score: " + std::to_string(readHighestScore()));
	m_HighestScoreText.setColor({ 0.f, 1.f, 0.f, 1.f });
	
	m_TextRenderer.init();

	m_ParticleRenderer.init();
	m_ParticleSys.setEmissionCount(100);
}

void DeadState::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			leftButtonPressed();
		}
	}
}

void DeadState::leftButtonPressed()
{
	if (Collision::isColliding(m_MouseRect, m_RetryRect))
	{
		AudioManager::getInstance().playSound("Click");
		StateManager::getInstance().clearAndPush(std::make_shared<MenuState>());
	}
	else if (Collision::isColliding(m_MouseRect, m_ExitRect))
	{
		AudioManager::getInstance().playSound("Click");
		SDL_Quit();
		exit(0);
	}
}

void DeadState::handleKeyPress(SDL_Keycode key) 
{

}

void DeadState::handleKeyRelease(SDL_Keycode key)
{

}

void DeadState::update(Uint32 delta) 
{
	m_MouseRect.position = Mouse::getPosition();
	
	m_ParticleSys.update(delta);
}

void DeadState::render()
{
	glClearColor(0.05f, 0.05f, 0.05f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_ParticleRenderer.render(m_ParticleSys);
	m_SpriteRenderer.render(m_Sprites, TextureManager::getInstance().getTexture("DeadSheet"));
	m_TextRenderer.render(m_ScoreText, TextureManager::getInstance().getTexture("TextSheet"));
	m_TextRenderer.render(m_HighestScoreText, TextureManager::getInstance().getTexture("TextSheet"));
}
