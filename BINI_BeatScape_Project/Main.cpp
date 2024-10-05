#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>

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
#include "SongSelect.h"

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
BINI::MainMenu* mainmenu = nullptr;
BINI::CompanyLogo* company = nullptr;
BINI::SongEasy* songeasy = new BINI::SongEasy(&renderer);

BINI::SongSelect songSelect(&renderer);

//Current Scene Pointer
BINI::Scene* currentScene = songeasy;

int main(int argc, char* args[])
{
	while (currentScene->handleEvents(&events))
	{
		//Clears screen
		renderer.clearScreen();

		//Scene manager
		if (currentScene->isDone() || currentScene == nullptr)
		{
			if (currentScene != nullptr)
			{
				delete currentScene;
				currentScene = nullptr;
			}

			switch (events.getCurrentState())
			{
			case BINI_LOGO:
				company = new BINI::CompanyLogo(&renderer);
				currentScene = company;
				break;
			case BINI_START:
				mainmenu = new BINI::MainMenu(&renderer);
				currentScene = mainmenu;
				break;
			case BINI_SONG_EASY:
				songeasy = new BINI::SongEasy(&renderer);
				currentScene = songeasy;
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
