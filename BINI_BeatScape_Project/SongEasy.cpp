#include "SongEasy.h"

namespace BINI
{
	SongEasy::SongEasy(BINI::Renderer* renderer)
	{
		//Textures
		background = new BINI::Texture(renderer, "assets/Cover_Images/BINI_COVER_6.png");
		overlay = new BINI::Texture(renderer, "assets/Cover_Images/SHADE.png");
		titlePanel = new BINI::Texture(renderer, "assets/textures/GAMEPLAY_ASSETS/SONG_TITLE_HEADER.png");
		accuracyPanel = new BINI::Texture(renderer, "assets/textures/GAMEPLAY_ASSETS/ACCURACY_HEADER.png");
		noteTexture = new BINI::Texture(renderer, "assets/textures/GAMEPLAY_ASSETS/SINGLE_NOTE.png");

		//Texture blend modes
		background->setBlendMode(SDL_BLENDMODE_BLEND);
		overlay->setBlendMode(SDL_BLENDMODE_BLEND);
		titlePanel->setBlendMode(SDL_BLENDMODE_BLEND);
		accuracyPanel->setBlendMode(SDL_BLENDMODE_BLEND);
		noteTexture->setBlendMode(SDL_BLENDMODE_BLEND);

		//Fonts and Labels
		steelar = new BINI::Font("assets/fonts/Steelar-j9Vnj.ttf", 24);
		bebas = new BINI::Font("assets/fonts/BebasNeue-Regular.ttf", 35);
		SDL_Color black = { 0, 0 ,0 };
		SDL_Color white = { 255, 255, 255 };
		title = new BINI::Labels(renderer, steelar, "ISLANG PANTROPIKO", white);
		bini = new BINI::Labels(renderer, bebas, "BINI", black);
		title->setBlendMode(SDL_BLENDMODE_BLEND);
		bini->setBlendMode(SDL_BLENDMODE_BLEND);

		//Audio
		song = new BINI::Music("assets/music/easy1.ogg");
		sfx = new BINI::SoundFX("assets/sfx/metronome.wav");
		
		//Timer
		timer = new BINI::Timer;
		timer->stop();

		//Parameters
		done = false;
		fadingIn = true;
		sceneAlpha = 0;
		beat = 1;
		noteY = -noteTexture->getHeight();
		noteVelocity = renderer->getMaxHeight() / 208;
		

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
			}
			else
			{
				sceneAlpha += 1;
			}
		}

		
		//Metronome
		if (timer->getTicks() % 625 <= 16 && timer->isStarted() && timer->getTicks() > 625)
		{
			std::cout << beat++ << "\n";
			if (beat <= 8)
				sfx->playSFX();
		}

		//Song controls
		if (beat == 6)
		{
			song->startMusic(0);
		}

		//Set Texture Alphas
		background->setAlpha(sceneAlpha);
		overlay->setAlpha(sceneAlpha * 4 / 5);
		titlePanel->setAlpha(sceneAlpha);
		accuracyPanel->setAlpha(sceneAlpha);
		noteTexture->setAlpha(sceneAlpha);
		title->setAlpha(sceneAlpha);
		bini->setAlpha(sceneAlpha);

		//Render textures
		background->render(renderer, 0, 0);
		overlay->render(renderer, 0, 0);
		titlePanel->render(renderer, 0, 0);
		accuracyPanel->render(renderer, renderer->getMaxWidth() - accuracyPanel->getWidth(), renderer->getMaxHeight() - accuracyPanel->getHeight());
		title->render(renderer, renderer->getMaxWidth() / 128, renderer->getMaxHeight() / 64);
		bini->render(renderer, renderer->getMaxWidth() / 128, titlePanel->getHeight() - (bini->getHeight() * 5 / 2));
		
		if (beat >= 6 && noteY <= renderer->getMaxHeight() + noteTexture->getHeight()) 
		{
			noteTexture->render(renderer, (renderer->getMaxWidth() / 2) - noteTexture->getWidth(), noteY += (int)noteVelocity);
		}
					

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