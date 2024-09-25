#pragma once

#include "SDL.h"

namespace BINI
{

	//Handles events.
	class Events
	{
	public:

		bool handleEvents();

	private:

		SDL_Event e;
	};
}


