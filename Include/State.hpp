#ifndef STATE_HPP
#define STATE_HPP

#include <SDL.h>

class State
{
public:
	virtual void init();

	virtual void handleEvent(const SDL_Event& event) = 0;
	virtual void handleKeyPress(SDL_Keycode key) = 0;
	virtual void handleKeyRelease(SDL_Keycode key) = 0;
	virtual void update(Uint32 delta) = 0;
	virtual void render() = 0;
};

#endif