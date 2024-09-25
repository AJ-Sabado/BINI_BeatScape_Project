#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "iostream"


namespace BINI 
{
	//Initializes SDL application.
	class Application
	{
	public:

		//Application constructor.
		Application();

		//Application deconstructor.
		~Application();

		//Returns true if SDL and SDL image is initialized.
		bool ready();

	private:
		bool success;
	};
}


