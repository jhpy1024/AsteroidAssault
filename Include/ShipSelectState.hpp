#ifndef SHIP_SELECT_STATE_HPP
#define SHIP_SELECT_STATE_HPP

#include "State.hpp"
#include <SDL.h>
#include "Player.hpp"
#include "Sprite.hpp"
#include "SpriteRenderer.hpp"
#include "RectangleShape.hpp"
#include <vector>

class ShipSelectState : public State
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
	
	void previousShip();
	void nextShip();

private:
	PlayerShipType m_CurrentShip;

	Sprite m_ShipPreview;
	Sprite m_LeftArrow;
	Sprite m_RightArrow;
	SpriteRenderer m_SpriteRenderer;
	std::vector<Sprite> m_Sprites;

	RectangleShape m_LeftRect;
	RectangleShape m_RightRect;
};

#endif