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
		
		if (e.type == SDL_KEYDOWN)
		{
			switch (currentState)
			{
			case BINI_START:
				mainMenuControls();
				break;
			}
		}		
	}

	return true;
}

int BINI::Events::getCurrentState()
{
	return currentState;
}

void BINI::Events::mainMenuControls()
{
	std::cout << "Key pressed.\n";
}