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
		
		//Events deconstructor.
		~Events();
		
		//Polls all pending events.
		int pollEvents();

		//Returns event type.
		Uint32 type();

		//Returns key code from an event.
		Uint32 getKey();

		//Returns true if key is polled repeatedly.
		bool repeat();

		//Returns current application state.
		int getCurrentState();

		//Changes application state
		void setState(int state);

	private:

		//SDL event
		SDL_Event e;

		//Current application state
		int currentState;
	};
}



