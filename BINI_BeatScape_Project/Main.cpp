#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

#include "Application.h"
#include "Window.h"
#include "Renderer.h"
#include "Events.h"
#include "Scene.h"
#include "MainMenu.h"
#include "SongEasy.h"
#include "States.h"
#include "Music.h"
#include "CompanyLogo.h"

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

//Scenes	*all of which extends the BINI::Scene class
BINI::MainMenu mainMenu(&renderer);
BINI::CompanyLogo companyLogo(&renderer);
BINI::SongEasy song(&renderer);

//Current Scene Pointer
BINI::Scene* currentScene = &mainMenu;

int main(int argc, char* args[])
{
	while (currentScene->handleEvents(&events))
	{
		//Clears screen
		renderer.clearScreen();

		//Scene manager
		if (currentScene->isDone())
		{
			switch (events.getCurrentState())
			{
			case BINI_LOGO:
				if (currentScene != &companyLogo)
				{
					currentScene = &companyLogo;
				}
				break;
			case BINI_START:

				break;
			case BINI_SONG_EASY:
				if (currentScene != &song)
				{
					currentScene = &song;
				}
				break;
			}
		}

		//Draw current screen
		currentScene->display(&renderer);

		//Update screen
		renderer.updateScreen();

	}

	return 0;
}
