#include "Event.h"

bool BINI::Event::handleEvent()
{
	while (SDL_PollEvent(&bEvent) != 0)
	{
		if (bEvent.type == SDL_QUIT)
		{
			return false;
		}
	}

	return true;
}