#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "iostream"


namespace BINI 
{
	//This class initializes and deinitializes SDL and SDL image.
	class Application
	{
	public:

		//Initializes SDL.
		Application();

		//Deinitializes SDL.
		~Application();

		//Returns true if SDL and SDL image is initialized.
		bool ready();

	private:
		bool success;
	};
}


