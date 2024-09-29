#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

#include "Application.h"
#include "Window.h"
#include "Renderer.h"
#include "Events.h"
#include "Background.h"
#include "States.h"

//Parameters for fine tuning.
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//SDL Application
BINI::Application application;

//Game Window
BINI::Window window(&application, SCREEN_WIDTH, SCREEN_HEIGHT);

//SDL Renderer
BINI::Renderer renderer(&window);

//Game Events
BINI::Events events;

//Game objects
BINI::Background logo(&renderer, "assets/textures/bg.png");

//Current Pointers
BINI::Background* currentBackground;

int main(int argc, char* args[])
{

	while (events.handleEvents())
	{
		renderer.clearScreen();

		//Manages Scenes *may be abstracted soon
		switch (events.getCurrentState())
		{
		case BINI_LOGO:
			if (currentBackground != &logo)
			{
				currentBackground = &logo;
			}
			currentBackground->draw(&renderer);
			break;
		}

		renderer.updateScreen();

	}

	return 0;
}