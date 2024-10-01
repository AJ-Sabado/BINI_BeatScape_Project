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
	
	if (TTF_Init() == -1)
	{
		std::cout << "SDL ttf failed to initialize! SDL ttf Error: " << TTF_GetError() << "\n";
		success = false;
	}

	if (success)
	{
		std::cout << "SDL and SDL image initialized.\n";
	}

}

BINI::Application::~Application()
{
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	std::cout << "SDL and SDL image closed.\n";
}

bool BINI::Application::ready()
{
	return success;
}

