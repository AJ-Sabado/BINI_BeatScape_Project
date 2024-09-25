#include "Events.h"


bool BINI::Events::handleEvents()
{
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}
	}

	return true;
}