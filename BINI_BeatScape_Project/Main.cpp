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
#include <math.h>

#include "Application.h"
#include "Window.h"
#include "Renderer.h"
#include "Events.h"
#include "Scene.h"
#include "MainMenu.h"
#include "SongEasy.h"
#include "SongMedium.h"
#include "SongHard.h"
#include "States.h"
#include "Music.h"
#include "CompanyLogo.h"
#include "SongSelect.h"
#include "Leaderboards.h"

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
BINI::CompanyLogo* company = new BINI::CompanyLogo(&renderer);
BINI::MainMenu* mainmenu = nullptr;
BINI::SongSelect* songSelect = nullptr;
BINI::Leaderboards* leaderboards = nullptr;
BINI::SongEasy* songeasy = nullptr;
BINI::SongMedium* songmedium = nullptr;
BINI::SongHard* songhard = nullptr;

//Current Scene Pointer
BINI::Scene* currentScene = company;

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
			case BINI_SONG_SELECT:
				songSelect = new BINI::SongSelect(&renderer);
				currentScene = songSelect;
				break;
			case BINI_LEADERBOARD:
				leaderboards = new BINI::Leaderboards(&renderer);
				currentScene = leaderboards;
				break;
			case BINI_SONG_EASY:
				songeasy = new BINI::SongEasy(&renderer);
				currentScene = songeasy;
				break;
			case BINI_SONG_MEDIUM:
				songmedium = new BINI::SongMedium(&renderer);
				currentScene = songmedium;
				break;
			case BINI_SONG_HARD:
				songhard = new BINI::SongHard(&renderer);
				currentScene = songhard;
				break;
			case BINI_EXIT:
				BINI::Music::fadeOutMusic(1000);
				SDL_Delay(1000);
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
