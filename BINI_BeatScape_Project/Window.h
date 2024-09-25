#pragma once

#include "SDL.h"
#include "iostream"
#include "Application.h"

namespace BINI
{
	
	//Wrapper for SDL window.
	class Window
	{
	public:

		//Creates new window.
		Window(BINI::Application application, int width, int height);

		//Deallocates created window.
		~Window();

		//Returns current window.
		SDL_Window* getWindow();
		int getWindowWidth();
		int getWindowHeight();

	private:

		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;
		SDL_Window* bWindow;
	};
}



