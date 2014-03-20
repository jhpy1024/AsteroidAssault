#include <SDL.h>

#include <GL/glew.h>
#include <GL/GL.h>

#include <iostream>
#include <string>

#include "ShaderManager.hpp"

SDL_Window* window;
SDL_GLContext glContext;

bool isRunning = true;

const std::string WINDOW_TITLE = "Asteroid Assault";
const int WINDOW_WIDTH = 700;
const int WINDOW_HEIGHT = 640;

Uint32 oldElapsedTime;

void initSDL()
{
	auto initResult = SDL_Init(SDL_INIT_EVERYTHING);

	if (initResult != 0)
	{
		auto error = SDL_GetError();
		std::cerr << "Error initializing SDL: " << error << std::endl;
		SDL_ClearError();
	}
}

void createWindow()
{
	window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
}

void createGLContext()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	SDL_GL_SetSwapInterval(1);

	glContext = SDL_GL_CreateContext(window);
}

void handleInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			isRunning = false;
	}
}

void update(Uint32 delta)
{
	
}

void render()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	

	SDL_GL_SwapWindow(window);
}

Uint32 calculateDelta()
{
	auto elapsedTime = SDL_GetTicks();
	auto delta = elapsedTime - oldElapsedTime;
	oldElapsedTime = elapsedTime;

	return delta;
}

void gameLoop()
{
	while (isRunning)
	{
		auto delta = calculateDelta();

		handleInput();
		update(delta);
		render();
	}
}

void initGlew()
{
	auto initStatus = glewInit();
	
	if (initStatus != GLEW_OK)
		std::cerr << "There was an error initializing GLEW:\n-> " << glewGetErrorString(initStatus) << std::endl;
}

int main(int argc, char* argv[])
{
	initSDL();
	createWindow();
	createGLContext();
	initGlew();

	gameLoop();

	SDL_Quit();
	return 0;
}