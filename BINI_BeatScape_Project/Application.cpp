#include "Application.h"

BINI::Application::Application()
{
	success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL failed to initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags) && success)
	{
		std::cout << "SDL image failed to initialize! SDL image Error: " << IMG_GetError() << "\n";
		success = false;
	}
}

BINI::Application::~Application()
{
	IMG_Quit();
	SDL_Quit();
}

bool BINI::Application::ready()
{
	return success;
}

