#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "iostream"

//Contains all classes and methods for BINI Beatscape Project.
namespace BINI 
{
	//Initializes SDL application.
	class Application
	{
	public:

		//Application constructor.
		Application();

		//Application destructor.
		~Application();

		//Returns true if SDL and SDL image is initialized.
		bool ready();

	private:
		//True if all components are successfuly initialized.
		bool success;
	};
}


