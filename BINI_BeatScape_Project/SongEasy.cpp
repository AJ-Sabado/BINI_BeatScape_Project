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
		basebar = new BINI::Texture(renderer, "assets/textures/GAMEPLAY_ASSETS/BASE.png");
		barHighlights = new BINI::Texture(renderer, "assets/textures/GAMEPLAY_ASSETS/Highlight.png");
		fret = new BINI::Texture(renderer, "assets/textures/GAMEPLAY_ASSETS/Fret.png");
		noteTexture = new BINI::Texture(renderer, "assets/textures/GAMEPLAY_ASSETS/SINGLE_NOTE.png");


		//Chart
		chartReader = new BINI::ChartReader();
		chart = chartReader->loadSong("charts/easy.bchart");

		//Rects
		basebarSize = { 0, 0, barHighlights->getWidth(), renderer->getMaxHeight()};

		//Texture blend modes
		background->setBlendMode(SDL_BLENDMODE_BLEND);
		overlay->setBlendMode(SDL_BLENDMODE_BLEND);
		titlePanel->setBlendMode(SDL_BLENDMODE_BLEND);
		accuracyPanel->setBlendMode(SDL_BLENDMODE_BLEND);
		basebar->setBlendMode(SDL_BLENDMODE_BLEND);
		barHighlights->setBlendMode(SDL_BLENDMODE_BLEND);
		fret->setBlendMode(SDL_BLENDMODE_BLEND);
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
		stepTimer = new BINI::Timer;
		stepTimer->stop();

		//Flags
		done = false;
		fadingIn = true;

		//Alphas
		sceneAlpha = 0;
		bar1Highlight = 0;
		bar2Highlight = 0;
		bar3Highlight = 0;
		bar4Highlight = 0;

		//Note Positions
		NOTE_POS1 = renderer->getMaxWidth() / 2 - fret->getWidth() * 3 / 8 - noteTexture->getWidth() / 2;
		NOTE_POS2 = renderer->getMaxWidth() / 2 - fret->getWidth() / 8 - noteTexture->getWidth() / 2;
		NOTE_POS3 = renderer->getMaxWidth() / 2 + fret->getWidth() / 8 - noteTexture->getWidth() / 2;
		NOTE_POS4 = renderer->getMaxWidth() / 2 + fret->getWidth() * 3 / 8 - noteTexture->getWidth() / 2;

		holdingD = false;
		holdingF = false;
		holdingJ = false;
		holdingK = false;

		beat = 1;
		noteYVelocity = (renderer->getMaxHeight() - accuracyPanel->getHeight() - fret->getHeight()) / 1.25;

		bar = currentBars.begin();

		std::cout << noteYVelocity << "\n";
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
			if (sceneAlpha + 2 > 255)
			{
				sceneAlpha = 255;
				fadingIn = false;
				timer->start();
			}
			else
			{
				sceneAlpha += 2;
			}
		}

		//Fade out
		if (!fadingIn && false)
		{

		}
		
		

		//Song controls
		if (beat == 6)
		{
			song->startMusic(0);
		}

		//Set Texture Alphas
		background->setAlpha(sceneAlpha);
		overlay->setAlpha(sceneAlpha * 5 / 6);
		titlePanel->setAlpha(sceneAlpha);
		accuracyPanel->setAlpha(sceneAlpha);
		basebar->setAlpha(sceneAlpha);
		fret->setAlpha(sceneAlpha);
		noteTexture->setAlpha(sceneAlpha);
		title->setAlpha(sceneAlpha);
		bini->setAlpha(sceneAlpha);

		//Render textures
		background->render(renderer, 0, 0);
		overlay->render(renderer, 0, 0);
		basebar->render(renderer, renderer->getMaxWidth() / 2 - fret->getWidth() * 3 / 8 - barHighlights->getWidth() / 2, 0, &basebarSize);
		basebar->render(renderer, renderer->getMaxWidth() / 2 - fret->getWidth() / 8 - barHighlights->getWidth() / 2, 0, &basebarSize);
		basebar->render(renderer, renderer->getMaxWidth() / 2 + fret->getWidth() / 4 - barHighlights->getWidth(), 0, &basebarSize);
		basebar->render(renderer, renderer->getMaxWidth() / 2 + fret->getWidth() / 2 - barHighlights->getWidth(), 0, &basebarSize);
	
			//Bar Highlights
		if (!holdingD)
			bar1Highlight = barHighlightsfadeOut(bar1Highlight);
		if (!holdingF)
			bar2Highlight = barHighlightsfadeOut(bar2Highlight);
		if (!holdingJ)
			bar3Highlight = barHighlightsfadeOut(bar3Highlight);
		if (!holdingK)
			bar4Highlight = barHighlightsfadeOut(bar4Highlight);

		barHighlights->setAlpha(bar1Highlight);
		barHighlights->render(renderer, renderer->getMaxWidth() / 2 - fret->getWidth() * 3 / 8 - barHighlights->getWidth() / 2, 0);
		barHighlights->setAlpha(bar2Highlight);
		barHighlights->render(renderer, renderer->getMaxWidth() / 2 - fret->getWidth() / 8 - barHighlights->getWidth() / 2, 0);
		barHighlights->setAlpha(bar3Highlight);
		barHighlights->render(renderer, renderer->getMaxWidth() / 2 + fret->getWidth() / 4 - barHighlights->getWidth(), 0);
		barHighlights->setAlpha(bar4Highlight);
		barHighlights->render(renderer, renderer->getMaxWidth() / 2 + fret->getWidth() / 2 - barHighlights->getWidth(), 0, 0);
		
		
		titlePanel->render(renderer, 0, 0);
		accuracyPanel->render(renderer, renderer->getMaxWidth() - accuracyPanel->getWidth(), renderer->getMaxHeight() - accuracyPanel->getHeight());
		title->render(renderer, renderer->getMaxWidth() / 128, renderer->getMaxHeight() / 64);
		bini->render(renderer, renderer->getMaxWidth() / 128, titlePanel->getHeight() - (bini->getHeight() * 5 / 2));
		
		//Frame independent calculations
		float timestep = 0;
		if (timer->isStarted())
		{
			timestep = stepTimer->getTicks() / 1000.f;
		}

		//Metronome
		if (timer->getTicks() % 625 <= 16 && timer->isStarted() && timer->getTicks() > 625)
		{
			
			if (beat <= 4)
				sfx->playSFX();
			
			if (!chart.empty() && beat > 2)
			{
				currentBars.push_back(chart.front());
				chart.pop();
			}
			
			beat++;
		}

		//Note Processing
		if (beat > 3 && !currentBars.empty())
		{
			for (bar = currentBars.begin(); bar != currentBars.end();)
			{
				if ((*bar) == NULL)
				{
					continue;
				}

				//Render current notes
				if ((*bar)->d != NULL && (*bar)->d->isAlive)
				{
					noteTexture->render(renderer, NOTE_POS1, (int)((*bar)->d->noteYPos += noteYVelocity * timestep));
				}

				if ((*bar)->f != NULL && (*bar)->f->isAlive)
				{
					noteTexture->render(renderer, NOTE_POS2, (int)((*bar)->f->noteYPos += noteYVelocity * timestep));
				}

				if ((*bar)->j != NULL && (*bar)->j->isAlive)
				{
					noteTexture->render(renderer, NOTE_POS3, (int)((*bar)->j->noteYPos += noteYVelocity * timestep));
				}

				if ((*bar)->k != NULL && (*bar)->k->isAlive)
				{
					noteTexture->render(renderer, NOTE_POS4, (int)((*bar)->k->noteYPos += noteYVelocity * timestep));
				}

				if ((*bar) != NULL)
					(*bar)->totalY += noteYVelocity * timestep;

				bar++;
			}
		}

		fret->render(renderer, renderer->getMaxWidth() / 2 - fret->getWidth() / 2, renderer->getMaxHeight() - accuracyPanel->getHeight() - fret->getHeight());

		stepTimer->start();
	}

	Uint8 SongEasy::barHighlightsfadeOut(Uint8 highlight)
	{
		if (highlight - 10 < 0)
		{
			return 0;
		}
		else
		{
			return highlight - 10;
		}
	}

	bool SongEasy::isDone()
	{
		return done;
	}

	bool SongEasy::handleEvents(BINI::Events* events)
	{
		float timingScore = 0;
		while (events->pollEvents() != 0)
		{
			//User exits
			if (events->type() == SDL_QUIT)
			{
				return false;
			}
			//if key is pressed down
			if (events->type() == SDL_KEYDOWN && !events->repeat() && !fadingIn)
			{
				switch (events->getKey())
				{
				case SDLK_d:
					
					bar1Highlight = 255;
					holdingD = true;

					std::cout << timer->getTicks() % 625 << "\n";


					if (timer->getTicks() % 625 <= 117 && timer->getTicks() && timer->getTicks() > 625)
					{
						timingScore = 1;
						std::cout << "Perfect Timing" << "\n";
						

					}
					else if (timer->getTicks() % 625 <= 167 && timer->getTicks() % 625 > 117 && timer->isStarted() && timer->getTicks() > 625)
					{
						timingScore = 0.5;
						std::cout << "Good Timing" << "\n";
						
					}
					else if (timer->getTicks() % 625 > 167 && timer->isStarted() && timer->getTicks() > 625)
					{
						std::cout << "Bad Timing" << "\n";
					}
					break;

				case SDLK_f:
					if (!currentBars.empty())
						//(*currentBars.begin())->f->isAlive = false;
					holdingF = true;
					bar2Highlight = 255;
					break;

				case SDLK_j:
					if (!currentBars.empty())
						//(*currentBars.begin())->j->isAlive = false;
					holdingJ = true;
					bar3Highlight = 255;
					break;

				case SDLK_k:
					if (!currentBars.empty())
						//(*currentBars.begin())->k->isAlive = false;
					holdingK = true;
					bar4Highlight = 255;
					break;
				}
			}

			//if key is released
			if (events->type() == SDL_KEYUP && !events->repeat() && !fadingIn)
			{
				switch (events->getKey())
				{
				case SDLK_d:
					holdingD = false;
					break;

				case SDLK_f:
					holdingF = false;
					break;

				case SDLK_j:
					holdingJ = false;
					break;

				case SDLK_k:
					holdingK = false;
					break;
				}

			}
		}

		return true;
	}
}