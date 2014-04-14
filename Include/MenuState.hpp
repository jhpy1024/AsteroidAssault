#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include "State.hpp"
#include "Sprite.hpp"
#include "SpriteRenderer.hpp"
#include "RectangleShape.hpp"

#include <vector>

class MenuState : public State
{
public:
	void init() override;

	void handleEvent(const SDL_Event& event) override;
	void handleKeyPress(SDL_Keycode key) override;
	void handleKeyRelease(SDL_Keycode key) override;
	void update(Uint32 delta) override;
	void render() override;

private:
	void leftButtonPressed();

private:
	Sprite m_Title;
	Sprite m_PlayButton;
	Sprite m_AboutButton;
	Sprite m_ExitButton;
	std::vector<Sprite> m_Sprites;
	SpriteRenderer m_SpriteRenderer;

	RectangleShape m_PlayRect;
	RectangleShape m_AboutRect;
	RectangleShape m_ExitRect;
	RectangleShape m_MouseRect;
};

#endif