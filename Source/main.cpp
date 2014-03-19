#include <SDL.h>

#include <GL/glew.h>
#include <GL/GL.h>

#include <iostream>
#include <string>

SDL_Window* window;
SDL_GLContext glContext;

bool isRunning = false;

const std::string WINDOW_TITLE = "Asteroid Assault";
const int WINDOW_WIDTH = 700;
const int WINDOW_HEIGHT = 640;

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

void update()
{

}

void render()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
		glColor3f(1.f, 0.f, 0.f);
		glVertex2f(-1.f, -1.f);

		glColor3f(0.f, 1.f, 0.f);
		glVertex2f(0.f, -1.f);

		glColor3f(0.f, 0.f, 1.f);
		glVertex2f(0.f, 0.f);

		glColor3f(0.f, 1.f, 1.f);
		glVertex2f(-1.f, 0.f);
	glEnd();

	SDL_GL_SwapWindow(window);
}

int main(int argc, char* argv[])
{
	initSDL();
	createWindow();
	createGLContext();

	isRunning = true;

	while (isRunning)
	{
		handleInput();
		update();
		render();

		SDL_Delay(20);
	}

	SDL_Quit();

	return 0;
}