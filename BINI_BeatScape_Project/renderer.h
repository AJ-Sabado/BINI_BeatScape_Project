#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Window.h"
#include "iostream"

namespace BINI
{
	//Contains SDL Renderer and methods surrounding the renderer.
	class Renderer
	{
	public:

		Renderer(BINI::Window window);

		~Renderer();

		//Clears the screen.
		void clearScreen();

		//Applies render copies and updates screen.
		void update();

	private:

		SDL_Renderer* bRenderer;
	};

}

