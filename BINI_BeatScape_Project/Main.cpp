#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

#include "Application.h"
#include "Window.h"
#include "Renderer.h"
#include "Events.h"
#include "Background.h"

//Parameters for fine tuning.

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* args[])
{
	BINI::Application application;
	BINI::Window window(&application, SCREEN_WIDTH, SCREEN_HEIGHT);
	BINI::Renderer renderer(&window);
	BINI::Events events;

	BINI::Background background(&renderer, "assets/textures/bg.png");

	while (events.handleEvents())
	{
		renderer.clearScreen();

		background.draw(&renderer);

		renderer.updateScreen();
	}

	return 0;
}