#ifndef ABOUT_STATE_HPP
#define ABOUT_STATE_HPP

#include "State.hpp"
#include "Sprite.hpp"
#include "SpriteRenderer.hpp"
#include "StarParticleSystem.hpp"
#include "ParticleRenderer.hpp"
#include "RectangleShape.hpp"
#include "Text.hpp"
#include "TextRenderer.hpp"

#include <vector>

class AboutState : public State
{
public:
	AboutState();

	void init() override;

	void handleEvent(const SDL_Event& event) override;
	void handleKeyPress(SDL_Keycode key) override;
	void handleKeyRelease(SDL_Keycode key) override;
	void update(Uint32 delta) override;
	void render() override;

private:
	void leftButtonPressed();

private:
	Sprite m_BackBtn;
	Sprite m_Title;
	SpriteRenderer m_SpriteRenderer;
	std::vector<Sprite> m_Sprites;

	Text m_ProgrammerText;
	Text m_ArtText;
	Text m_SoundsText;
	Text m_ForText;
	TextRenderer m_TextRenderer;
	std::vector<Text> m_Text;

	RectangleShape m_BackRect;
	RectangleShape m_MouseRect;

	StarParticleSystem m_ParticleSys;
	ParticleRenderer m_ParticleRenderer;
};

#endif