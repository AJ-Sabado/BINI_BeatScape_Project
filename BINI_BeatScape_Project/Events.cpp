#include "Events.h"

BINI::Events::Events()
{
	currentState = BINI_START;
}

bool BINI::Events::handleEvents()
{
	while (SDL_PollEvent(&e) != 0)
	{
		//User exits
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		
		//State-specific event handlings
		switch (currentState)
		{
		case BINI_START:
			mainMenuControls();
			break;
		}
	}

	return true;
}

int BINI::Events::getCurrentState()
{
	return currentState;
}

//Put controls for Main Menu Here
void BINI::Events::mainMenuControls()
{
	//if key is pressed down
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_DOWN:
			std::cout << "Down key pressed.\n";
			break;
		}
	}
}