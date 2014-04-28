#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include "State.hpp"
#include "Sprite.hpp"
#include "SpriteRenderer.hpp"
#include "RectangleShape.hpp"
#include "StarParticleSystem.hpp"
#include "ParticleRenderer.hpp"

#include <vector>

class MenuState : public State
{
public:
	MenuState();

	void init() override;

	void handleEvent(const SDL_Event& event) override;
	void handleKeyPress(SDL_Keycode key) override;
	void handleKeyRelease(SDL_Keycode key) override;
	void update(Uint32 delta) override;
	void render() override;

private:
	void leftButtonPressed();
	void updateSlider(Sprite& slider, Sprite& sliderBackground, RectangleShape& sliderRect);
	int calculateVolume(Sprite& slider, Sprite& sliderBackground);

private:
	Sprite m_Title;
	Sprite m_PlayButton;
	Sprite m_AboutButton;
	Sprite m_ExitButton;
	Sprite m_MusicSliderBackground;
	Sprite m_SoundSliderBackground;
	Sprite m_MusicSlider;
	Sprite m_SoundSlider;
	std::vector<Sprite> m_Sprites;
	SpriteRenderer m_SpriteRenderer;

	bool m_IsSlidingMusic;
	bool m_IsSlidingSound;

	RectangleShape m_PlayRect;
	RectangleShape m_AboutRect;
	RectangleShape m_ExitRect;
	RectangleShape m_MouseRect;
	RectangleShape m_SoundSliderRect;
	RectangleShape m_MusicSliderRect;

	StarParticleSystem m_ParticleSys;
	ParticleRenderer m_ParticleRenderer;
};

#endif