#ifndef DEAD_STATE_HPP
#define DEAD_STATE_HPP

#include "State.hpp"
#include "Text.hpp"
#include "SpriteRenderer.hpp"
#include "Sprite.hpp"
#include "RectangleShape.hpp"
#include "TextRenderer.hpp"
#include "StarParticleSystem.hpp"
#include "ParticleRenderer.hpp"

#include <vector>

class DeadState : public State
{
public:
	DeadState(int score);

	void init() override;

	void handleEvent(const SDL_Event& event) override;
	void handleKeyPress(SDL_Keycode key) override;
	void handleKeyRelease(SDL_Keycode key) override;
	void update(Uint32 delta) override;
	void render() override;

private:
	void leftButtonPressed();

	int readHighestScore() const;
	void writeHighestScore();

private:
	Sprite m_Title;
	Sprite m_RetryButton;
	Sprite m_ExitButton;
	std::vector<Sprite> m_Sprites;
	SpriteRenderer m_SpriteRenderer;

	RectangleShape m_RetryRect;
	RectangleShape m_ExitRect;
	RectangleShape m_MouseRect;

	Text m_ScoreText;
	Text m_HighestScoreText;
	TextRenderer m_TextRenderer;

	StarParticleSystem m_ParticleSys;
	ParticleRenderer m_ParticleRenderer;

	int m_Score;
};

#endif