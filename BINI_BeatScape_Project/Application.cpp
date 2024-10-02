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

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL mixer failed to initialize! SDL mixer Error: " << Mix_GetError() << "\n";
		success = false;
	}

	if (success)
	{
		std::cout << "SDL, SDL image, SDL ttf, and SDL mixer initialized.\n";
	}

}

BINI::Application::~Application()
{
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	std::cout << "SDL, SDL image, SDL ttf, and SDL mixer closed.\n";
}

bool BINI::Application::ready()
{
	return success;
}

