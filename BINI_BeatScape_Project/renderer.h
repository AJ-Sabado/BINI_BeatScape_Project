#pragma once

#include "Window.h"

namespace BINI
{
	//Contains SDL renderer.
	class Renderer
	{
	public:

		//Renderer constructor.
		Renderer(BINI::Window* window);

		//Renderer deconstructor.
		~Renderer();

		//Returns SDL renderer
		inline SDL_Renderer* getRenderer() { return bRenderer; }

		//Clears the screen.
		void clearScreen();

		//Updates all changes to the renderer.
		void updateScreen();

	private:

		SDL_Renderer* bRenderer;
	};
}

