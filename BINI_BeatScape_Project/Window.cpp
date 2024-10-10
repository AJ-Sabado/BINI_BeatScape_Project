#include "Window.h"

BINI::Window::Window(BINI::Application* application, int width, int height)
{
	SCREEN_WIDTH = 0;
	SCREEN_HEIGHT = 0;
	bWindow = NULL;

	if (application->ready())
	{
		SCREEN_WIDTH = width;
		SCREEN_HEIGHT = height;
		bWindow = SDL_CreateWindow("BINI BeatScape", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (bWindow == NULL)
		{
			std::cout << "Unable to create new window. SDL Error: " << SDL_GetError() << "\n";
		}
		else
		{
			std::cout << "Window created.\n";
		}
	}
}

BINI::Window::~Window()
{
	SDL_DestroyWindow(bWindow);
	bWindow = NULL;
	std::cout << "Window destroyed.\n";
}

int BINI::Window::getWindowWidth()
{
	return SCREEN_WIDTH;
}

int BINI::Window::getWindowHeight()
{
	return SCREEN_HEIGHT;
}
