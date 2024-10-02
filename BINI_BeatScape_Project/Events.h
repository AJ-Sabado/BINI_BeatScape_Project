#pragma once

#include "SDL.h"
#include "States.h"
#include "SoundFX.h"
#include "iostream"

namespace BINI
{

	//Handles events.
	class Events
	{
	public:
		//Events constructor.
		Events();

		~Events();

		//Handles currently pending events. Returns false if user quits.
		bool handleEvents();

		//Returns current application state.
		int getCurrentState();


	private:

		//SDL event
		SDL_Event e;

		//Current application state
		int currentState;

		//Specific event handling for main menu state		*to be refactored
		void mainMenuControls();

	};
}



