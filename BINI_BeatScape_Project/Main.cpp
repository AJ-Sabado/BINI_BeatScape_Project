#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

#include "Application.h"
#include "Window.h"
#include "Renderer.h"
#include "Event.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* args[])
{
	BINI::Application application;
	BINI::Window window(application, SCREEN_WIDTH, SCREEN_HEIGHT);
	BINI::Renderer renderer(window);
	BINI::Event event;

	while (event.handleEvent())
	{
		renderer.clearScreen();

		renderer.update();
	}

	return 0;
}