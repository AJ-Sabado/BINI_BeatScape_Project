#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

#include "Application.h"
#include "Window.h"
#include "Renderer.h"
#include "Events.h"
#include "Scene.h"
#include "MainMenu.h"
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

//Scenes
BINI::MainMenu mainMenu(&renderer);

//Current Scene Pointer
BINI::Scene* currentScene;

int main(int argc, char* args[])
{

	while (events.handleEvents())
	{
		renderer.clearScreen();

		//Manages Scenes *may be abstracted soon
		switch (events.getCurrentState())
		{
		case BINI_START:
			if (currentScene != &mainMenu)
			{
				currentScene = &mainMenu;
			}
			currentScene->display(&renderer);
			break;
		}

		renderer.updateScreen();

	}

	return 0;
}
