#pragma once

#include "SDL.h"
#include "States.h"
#include "iostream"

namespace BINI
{

	//Handles events.
	class Events
	{
	public:

		Events();

		bool handleEvents();

		int getCurrentState();


	private:

		SDL_Event e;

		int currentState;

		void mainMenuControls();
	};
}



