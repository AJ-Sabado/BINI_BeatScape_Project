#include "Events.h"

BINI::Events::Events()
{
	currentState = BINI_START;
}

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

int BINI::Events::getCurrentState()
{
	return currentState;
}