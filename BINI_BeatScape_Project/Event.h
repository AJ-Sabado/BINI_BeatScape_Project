#pragma once

#include "SDL.h"

namespace BINI
{
	class Event
	{
	public:

		//Handle events and state changes
		bool handleEvent();

	private:

		SDL_Event bEvent;
	};
}


