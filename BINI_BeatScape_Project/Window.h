#pragma once

#include "Application.h"

namespace BINI
{
	
	//Contains SDL window.
	class Window
	{
	public:

		//Window constructor.
		Window(BINI::Application* application, int width, int height);

		//Deallocates created window.
		~Window();

		//Returns current window.
		inline SDL_Window* getCurrentWindow() { return bWindow; }

		//Returns window width.
		int getWindowWidth();

		//Returns window height.
		int getWindowHeight();

	private:

		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;
		SDL_Window* bWindow;
	};
}



