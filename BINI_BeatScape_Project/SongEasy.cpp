#include "SongEasy.h"

namespace BINI
{
	SongEasy::SongEasy(BINI::Renderer* renderer)
	{
		background = new BINI::Texture(renderer, "assets/Cover_Images/BINI_COVER_6.png");
		overlay = new BINI::Texture(renderer, "assets/Cover_Images/SHADE.png");
		titlePanel = new BINI::Texture(renderer, "assets/textures/GAMEPLAY_ASSETS/SONG_TITLE_HEADER.png");
		accuracyPanel = new BINI::Texture(renderer, "assets/textures/GAMEPLAY_ASSETS/ACCURACY_HEADER.png");
		noteTexture = new BINI::Texture(renderer, "assets/textures/GAMEPLAY_ASSETS/SINGLE_NOTE.png");

		background->setBlendMode(SDL_BLENDMODE_BLEND);
		overlay->setBlendMode(SDL_BLENDMODE_BLEND);
		titlePanel->setBlendMode(SDL_BLENDMODE_BLEND);
		accuracyPanel->setBlendMode(SDL_BLENDMODE_BLEND);
		noteTexture->setBlendMode(SDL_BLENDMODE_BLEND);

		song = new BINI::Music("assets/music/easy1.ogg");
		sfx = new BINI::SoundFX("assets/sfx/metronome.wav");
		timer = new BINI::Timer;
		timer->stop();

		done = false;
		fadingIn = true;
		sceneAlpha = 0;
		beat = 0;
		noteY = -noteTexture->getHeight();
		

	}

	SongEasy::~SongEasy()
	{
		//Cleanup

		done = false;
		fadingIn = true;
		sceneAlpha = 0;

		if (background != NULL)
		{
			delete background;
			background = NULL;
		}

		if (overlay != NULL)
		{
			delete overlay;
			overlay = NULL;
		}

		if (titlePanel != NULL)
		{
			delete titlePanel;
			titlePanel = NULL;
		}

		if (song != NULL)
		{
			delete song;
			song = NULL;
		}

		if (sfx != NULL)
		{
			delete sfx;
			sfx = NULL;
		}

		if (timer != NULL)
		{
			delete timer;
			timer = NULL;
		}
	}

	void SongEasy::display(BINI::Renderer* renderer)
	{

		//Fade in;
		if (fadingIn)
		{
			if (sceneAlpha + 1 > 255)
			{
				sceneAlpha = 255;
				fadingIn = false;
				timer->start();
				song->startMusic(0);
				std::cout << "Song is starting.\n";
			}
			else
			{
				sceneAlpha += 1;
			}
		}

		

		if (timer->getTicks() % 625 <= 17 && timer->isStarted())
		{
			std::cout << beat++ << "\n";
			sfx->playSFX();
		}

		//Set Texture Alphas
		background->setAlpha(sceneAlpha);
		overlay->setAlpha(sceneAlpha * 4 / 5);
		titlePanel->setAlpha(sceneAlpha);
		accuracyPanel->setAlpha(sceneAlpha);
		noteTexture->setAlpha(sceneAlpha);

		//Render textures
		background->render(renderer, 0, 0);
		overlay->render(renderer, 0, 0);
		titlePanel->render(renderer, 0, 0);
		accuracyPanel->render(renderer, renderer->getMaxWidth() - accuracyPanel->getWidth(), renderer->getMaxHeight() - accuracyPanel->getHeight());
		if (timer->isStarted() && noteY != renderer->getMaxHeight() + noteTexture->getHeight())
			noteTexture->render(renderer, (renderer->getMaxWidth() / 2) - noteTexture->getWidth(), noteY += 5);		

	}

	bool SongEasy::isDone()
	{
		return done;
	}

	bool SongEasy::handleEvents(BINI::Events* events)
	{
		while (events->pollEvents() != 0)
		{
			//User exits
			if (events->type() == SDL_QUIT)
			{
				return false;
			}

			//if key is pressed down
			if (events->type() == SDL_KEYDOWN && !events->repeat())
			{
				switch (events->getKey())
				{
				case SDLK_DOWN:
					
					break;
				}
			}

			//if key is released
			if (events->type() == SDL_KEYUP && !events->repeat())
			{
				switch (events->getKey())
				{
				case SDLK_DOWN:
					
					break;
				}
			}
		}

		return true;
	}
}