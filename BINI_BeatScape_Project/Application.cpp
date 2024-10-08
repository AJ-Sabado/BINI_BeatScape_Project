#include "Application.h"

BINI::Application::Application()
{
	success = true;

	//Intializes SDL video
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL failed to initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}

	//Initializes SDL image
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags) && success)
	{
		std::cout << "SDL image failed to initialize! SDL image Error: " << IMG_GetError() << "\n";
		success = false;
	}
	
	//Initializes SDL font
	if (TTF_Init() == -1)
	{
		std::cout << "SDL ttf failed to initialize! SDL ttf Error: " << TTF_GetError() << "\n";
		success = false;
	}

	//Intializes SDL mixer for audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL mixer failed to initialize! SDL mixer Error: " << Mix_GetError() << "\n";
		success = false;
	}

	//Turns linear texture filtering on to reduce jaggedness.
	if (success)
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning: Linear texture filtering not enabled!\n";
		}
		std::cout << "SDL, SDL image, SDL ttf, and SDL mixer initialized.\n";
	}

}

BINI::Application::~Application()
{
	//Component cleanup
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

