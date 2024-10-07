#include "SongEasy.h"

enum NOTE_ACCURACY {
	NO_INPUT,
	PERFECT,
	GOOD,
	MISS
};

namespace BINI
{
	SongEasy::SongEasy(BINI::Renderer* renderer)
	{
		//Textures
		background = new BINI::Texture(renderer, backgroundPath);
		overlay = new BINI::Texture(renderer, "assets/Cover_Images/SHADE.png");
		titlePanel = new BINI::Texture(renderer, "assets/textures/GAMEPLAY_ASSETS/SONG_TITLE_HEADER.png");
		accuracyPanel = new BINI::Texture(renderer, "assets/textures/GAMEPLAY_ASSETS/ACCURACY_HEADER.png");
		basebar = new BINI::Texture(renderer, "assets/textures/GAMEPLAY_ASSETS/BASE.png");
		barHighlights = new BINI::Texture(renderer, "assets/textures/GAMEPLAY_ASSETS/Highlight.png");
		fret = new BINI::Texture(renderer, "assets/textures/GAMEPLAY_ASSETS/Fret.png");
		noteTexture = new BINI::Texture(renderer, "assets/textures/GAMEPLAY_ASSETS/SINGLE_NOTE.png");

		//Chart
		chartReader = new BINI::ChartReader();
		chart = chartReader->loadSong(chartPath);

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

		//Fonts
		steelar = new BINI::Font("assets/fonts/Steelar-j9Vnj.ttf", 25);
		bebas = new BINI::Font("assets/fonts/BebasNeue-Regular.ttf", 35);
		steelarBig = new BINI::Font("assets/fonts/Steelar-j9Vnj.ttf", 35);
		bebasBig = new BINI::Font("assets/fonts/BebasNeue-Regular.ttf", 45);
		black = { 0, 0 ,0 };
		white = { 255, 255, 255 };

		//Labels
		title = new BINI::Labels(renderer, steelar, songTitle, white);
		bini = new BINI::Labels(renderer, bebas, "BINI", black);
		accuracyLabel = new BINI::Labels(renderer, bebas, "100.00%", black);
		scoreLabel = new BINI::Labels(renderer, steelar, "0", white);
		comboHeader = new BINI::Labels(renderer, bebas, "Combo", white);
		comboCounter = new BINI::Labels(renderer, bebasBig, "0", white);
		noteHit = new BINI::Labels(renderer, steelarBig, "ready", white);
		DButton = new BINI::Labels(renderer, bebasBig, "D", white);
		FButton = new BINI::Labels(renderer, bebasBig, "F", white);
		JButton = new BINI::Labels(renderer, bebasBig, "J", white);
		KButton = new BINI::Labels(renderer, bebasBig, "K", white);

		title->setBlendMode(SDL_BLENDMODE_BLEND);
		bini->setBlendMode(SDL_BLENDMODE_BLEND);
		accuracyLabel->setBlendMode(SDL_BLENDMODE_BLEND);
		scoreLabel->setBlendMode(SDL_BLENDMODE_BLEND);
		comboHeader->setBlendMode(SDL_BLENDMODE_BLEND);
		comboCounter->setBlendMode(SDL_BLENDMODE_BLEND);
		noteHit->setBlendMode(SDL_BLENDMODE_BLEND);
		DButton->setBlendMode(SDL_BLENDMODE_BLEND);
		FButton->setBlendMode(SDL_BLENDMODE_BLEND);
		JButton->setBlendMode(SDL_BLENDMODE_BLEND);
		KButton->setBlendMode(SDL_BLENDMODE_BLEND);



		//Audio
		song = new BINI::Music(musicPath);
		sfx = new BINI::SoundFX("assets/sfx/metronome.wav");
		
		//Timer
		timer = new BINI::Timer;
		timer->stop();
		stepTimer = new BINI::Timer;
		stepTimer->stop();
		songDurationTimer = new BINI::Timer;
		songDurationTimer->stop();

		//Flags
		done = false;
		fadingIn = true;
		isPaused = false;

		//Alphas
		sceneAlpha = 0;
		bar1Highlight = 0;
		bar2Highlight = 0;
		bar3Highlight = 0;
		bar4Highlight = 0;
		infoAlpha = 0;
		noteHitAlpha = 0;

		//Note Positions
		NOTE_POS1 = renderer->getMaxWidth() / 2 - fret->getWidth() * 3 / 8 - noteTexture->getWidth() / 2;
		NOTE_POS2 = renderer->getMaxWidth() / 2 - fret->getWidth() / 8 - noteTexture->getWidth() / 2;
		NOTE_POS3 = renderer->getMaxWidth() / 2 + fret->getWidth() / 8 - noteTexture->getWidth() / 2;
		NOTE_POS4 = renderer->getMaxWidth() / 2 + fret->getWidth() * 3 / 8 - noteTexture->getWidth() / 2;

		holdingD = false;
		holdingF = false;
		holdingJ = false;
		holdingK = false;

		//Metronome Calcs
		beat = 0;
		oldBeat = 0;
		currentBeat = 0;
		bps = (float)bpm / 60;

		//Note Hit
		noteHitValue = NO_INPUT;
		beatDuration = 0;
		lastBeatDuration = 0;
		notePassedBarrier = (renderer->getMaxHeight() - accuracyPanel->getHeight() - fret->getHeight()) / 2 + noteTexture->getHeight();

		//Note velocity
		noteScrollTime = 120.f / bpm;
		noteYVelocity = (renderer->getMaxHeight() - accuracyPanel->getHeight() - fret->getHeight()) / noteScrollTime;
		bar = currentBars.begin();
		
	}

	SongEasy::~SongEasy()
	{
		//Cleanup
		done = false;
		fadingIn = true;
		sceneAlpha = 0;

		holdingD = false;
		holdingF = false;
		holdingJ = false;
		holdingK = false;

		beat = 0;
		oldBeat = 0;
		currentBeat = 0;
		bps = 1.6;

		done = false;
		fadingIn = true;

		currentBars.clear();

		//Textures Cleanup
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

		if (accuracyPanel != NULL)
		{
			delete accuracyPanel;
			accuracyPanel = NULL;
		}

		if (basebar != NULL)
		{
			delete basebar;
			basebar = NULL;
		}

		if (barHighlights != NULL)
		{
			delete barHighlights;
			barHighlights = NULL;
		}

		if (fret != NULL)
		{
			delete fret;
			fret = NULL;
		}

		if (noteTexture != NULL)
		{
			delete noteTexture;
			noteTexture = NULL;
		}

		//Audio Cleanup
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

		//Font Cleanup
		if (steelar != NULL)
		{
			delete steelar;
			steelar = NULL;
		}

		if (bebas != NULL)
		{
			delete bebas;
			bebas = NULL;
		}

		//Labels cleanup
		if (title != NULL)
		{
			delete title;
			title = NULL;
		}

		if (bini != NULL)
		{
			delete bini;
			bini = NULL;
		}

		if (accuracyLabel != NULL)
		{
			delete accuracyLabel;
			accuracyLabel = NULL;
		}

		if (scoreLabel != NULL)
		{
			delete scoreLabel;
			scoreLabel = NULL;
		}
	}

	void SongEasy::display(BINI::Renderer* renderer)
	{
		//Beat pulse
		if (timer->isStarted() && !isPaused)
		{
			float beatGlide = timer->getTicks() * bps / 1000.f;
			currentBeat = (int)(beatGlide);
		}
		
		//Max Combo Counter
		if (currentCombo > maxCombo)
		{
			maxCombo = currentCombo;
		}


		//Metronome
		if (currentBeat > oldBeat && timer->isStarted())
		{
			oldBeat = currentBeat;
			beat++;
			beatDuration = songDurationTimer->getTicks();
			songDurationTimer->start();
			if (beat <= 4)
				sfx->playSFX();
			if (!chart.empty() && beat >= 3)
			{
				if (chart.front() != NULL)
					currentBars.push_back(chart.front());
				chart.pop();
			}
		}

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
		if (beat > 356 || accuracy < 65.f)
		{
			if (accuracy < 95.f && sceneAlpha == 255)
			{
				song->fadeOutMusic(1000);
			}
			
			if (sceneAlpha - 2 < 0)
			{
				sceneAlpha = 0;
				stringStream.clear();
				done = true;
			}
			else
			{
				sceneAlpha -= 2;
			}
		}
		
		

		//Song controls
		if (beat == 5 && !song->isPlaying())
		{
			song->startMusic(0);
			songDurationTimer->start();
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
		accuracyLabel->setAlpha(sceneAlpha);

		

		//Render static textures
		background->render(renderer, 0, 0);
		overlay->render(renderer, 0, 0);
		basebar->render(renderer, renderer->getMaxWidth() / 2 - fret->getWidth() * 3 / 8 - barHighlights->getWidth() / 2, 0, &basebarSize);
		basebar->render(renderer, renderer->getMaxWidth() / 2 - fret->getWidth() / 8 - barHighlights->getWidth() / 2, 0, &basebarSize);
		basebar->render(renderer, renderer->getMaxWidth() / 2 + fret->getWidth() / 4 - barHighlights->getWidth(), 0, &basebarSize);
		basebar->render(renderer, renderer->getMaxWidth() / 2 + fret->getWidth() / 2 - barHighlights->getWidth(), 0, &basebarSize);
	
			//Bar Highlights Modulation
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
		
		
		
		//Frame independent calculations
		float timestep = 0;
		if (timer->isStarted())
		{
			timestep = stepTimer->getTicks() / 1000.f;
		}

		//Note Processing
		if (beat >= 3 && !currentBars.empty() && !isPaused)
		{
			for (bar = currentBars.begin(); bar != currentBars.end();)
			{

				if (currentBars.empty())
				{
					continue;
				}

				//Non empty bar with no notes / Base Case
				if (currentBars.front()->d == NULL && currentBars.front()->f == NULL && currentBars.front()->j == NULL && currentBars.front()->k == NULL && currentBars.front() != NULL)
				{
					bar = currentBars.erase(currentBars.begin());
					if (currentBars.empty())
					{
						continue;
					}
				}
				
				//Miss Bar
				if (currentBars.front() != NULL && currentBars.front()->totalY > renderer->getMaxHeight() + noteTexture->getHeight())
				{
					if (currentBars.front()->d != NULL || currentBars.front()->f != NULL || currentBars.front()->j != NULL || currentBars.front()->k != NULL)
					{
						currentCombo = 0;
						--perfectNotes;
						noteHitValue = MISS;
						noteHitAlpha = 255;
					}
					bar = currentBars.erase(currentBars.begin());
					if (currentBars.empty())
					{
						continue;
					}
				}
				

				//Scoring
					//D
				if (currentBars.front() != NULL && currentBars.front()->d != NULL && dScoreQ != 0)
				{

					noteHitAlpha = 255;
					if (currentBars.front()->d->noteYPos < notePassedBarrier)
					{
						dScoreQ = MISS;

					}
					noteHitValue = dScoreQ;
					delete currentBars.front()->d;
					currentBars.front()->d = NULL;
					
					switch (dScoreQ)
					{
					case PERFECT:
						score += (int)(maxScore / maxNotes);
						currentCombo++;
						break;
					case GOOD:
						score += (int)(maxScore / maxNotes / 4);
						currentCombo++;
						--perfectNotes;
						break;
					case MISS:
						currentCombo = 0;
						perfectNotes-=2;
						break;
					}
					dScoreQ = 0;
				}
				else if (dScoreQ != 0)
				{
					if (currentBars.front() == NULL || currentBars.front()->d == NULL)
					{
						currentCombo = 0;
						perfectNotes -= 2;
						noteHitAlpha = 255;
						noteHitValue = MISS;
						dScoreQ = 0;
					}
				}

					//F
				if (currentBars.front() != NULL && currentBars.front()->f != NULL && fScoreQ != 0)
				{
					noteHitAlpha = 255;
					
					if (currentBars.front()->f->noteYPos < notePassedBarrier)
					{
						fScoreQ = MISS;
					}
					noteHitValue = fScoreQ;
					delete currentBars.front()->f;
					currentBars.front()->f = NULL;
					switch (fScoreQ)
					{
					case PERFECT:
						score += (int)(maxScore / maxNotes);
						currentCombo++;
						break;
					case GOOD:
						score += (int)(maxScore / maxNotes / 4);
						currentCombo++;
						--perfectNotes;
						break;
					case MISS:
						currentCombo = 0;
						perfectNotes-=2;
						break;
					}
					fScoreQ = 0;
				}
				else if (fScoreQ != 0)
				{
					if (currentBars.front() == NULL || currentBars.front()->f == NULL)
					{
						currentCombo = 0;
						perfectNotes -= 2;
						noteHitAlpha = 255;
						noteHitValue = MISS;
						fScoreQ = 0;
					}
				}
					//J
				if (currentBars.front() != NULL && currentBars.front()->j != NULL && jScoreQ != 0)
				{
					noteHitAlpha = 255;
					
					if (currentBars.front()->j->noteYPos < notePassedBarrier)
					{
						jScoreQ = MISS;
					}
					noteHitValue = jScoreQ;
					delete currentBars.front()->j;
					currentBars.front()->j = NULL;
					switch (jScoreQ)
					{
					case PERFECT:
						score += (int)(maxScore / maxNotes);
						currentCombo++;
						break;
					case GOOD:
						score += (int)(maxScore / maxNotes / 4);
						currentCombo++;
						--perfectNotes;
						break;
					case MISS:
						currentCombo = 0;
						perfectNotes-=2;
						break;
					}
					jScoreQ = 0;
				}
				else if (jScoreQ != 0)
				{
					if (currentBars.front() == NULL || currentBars.front()->j == NULL)
					{
						currentCombo = 0;
						perfectNotes -= 2;
						noteHitAlpha = 255;
						noteHitValue = MISS;
						jScoreQ = 0;
					}
				}

					//K
				if (currentBars.front() != NULL && currentBars.front()->k != NULL && kScoreQ != 0)
				{
					noteHitAlpha = 255;
					if (currentBars.front()->k->noteYPos < notePassedBarrier)
					{
						kScoreQ = MISS;
					}
					noteHitValue = kScoreQ;
					delete currentBars.front()->k;
					currentBars.front()->k = NULL;
					switch (kScoreQ)
					{
					case PERFECT:
						score += (int)(maxScore / maxNotes);
						currentCombo++;
						break;
					case GOOD:
						score += (int)(maxScore / maxNotes / 4);
						currentCombo++;
						--perfectNotes;
						break;
					case MISS:
						currentCombo = 0;
						perfectNotes-=2;
						break;
					}
					kScoreQ = 0;
				}
				else if (kScoreQ != 0)
				{
					if (currentBars.front() == NULL || currentBars.front()->k == NULL)
					{
						currentCombo = 0;
						perfectNotes -= 2;
						noteHitAlpha = 255;
						noteHitValue = MISS;
						kScoreQ = 0;
					}
				}

				//Render current notes
				if ((*bar)->d != NULL)
				{
					noteTexture->render(renderer, NOTE_POS1, (int)((*bar)->d->noteYPos += noteYVelocity * timestep));
				}

				if ((*bar)->f != NULL)
				{
					noteTexture->render(renderer, NOTE_POS2, (int)((*bar)->f->noteYPos += noteYVelocity * timestep));
				}

				if ((*bar)->j != NULL)
				{
					noteTexture->render(renderer, NOTE_POS3, (int)((*bar)->j->noteYPos += noteYVelocity * timestep));
				}

				if ((*bar)->k != NULL)
				{
					noteTexture->render(renderer, NOTE_POS4, (int)((*bar)->k->noteYPos += noteYVelocity * timestep));
				}

				if ((*bar) != NULL)
					(*bar)->totalY += noteYVelocity * timestep;

				bar++;
			}
		}

		fret->render(renderer, renderer->getMaxWidth() / 2 - fret->getWidth() / 2, renderer->getMaxHeight() - accuracyPanel->getHeight() - fret->getHeight());
		
		titlePanel->render(renderer, 0, 0);
		accuracyPanel->render(renderer, renderer->getMaxWidth() - accuracyPanel->getWidth(), renderer->getMaxHeight() - accuracyPanel->getHeight());
		title->render(renderer, renderer->getMaxWidth() / 128, renderer->getMaxHeight() / 64);
		bini->render(renderer, renderer->getMaxWidth() / 128, titlePanel->getHeight() - (bini->getHeight() * 5 / 2));
		
		accuracy = 100.f * perfectNotes / maxNotes;
		stringStream.str("");
		stringStream << std::fixed << std::setprecision(2) << accuracy << "%";

		accuracyLabel->setText(renderer, bebas, stringStream.str().c_str(), black);
		accuracyLabel->render(renderer, renderer->getMaxWidth() - accuracyLabel->getWidth() * 3 / 2, renderer->getMaxHeight() - accuracyPanel->getHeight() / 2 - accuracyLabel->getHeight());

		stringStream.str("");
		stringStream << score;

		scoreLabel->setText(renderer, steelar, stringStream.str().c_str(), white);
		scoreLabel->render(renderer, renderer->getMaxWidth() - scoreLabel->getWidth() / 2 - accuracyLabel->getWidth() * 3 / 2, renderer->getMaxHeight() - scoreLabel->getHeight() * 2);

		//Info Alphas
		
		stringStream.str("");
		stringStream << currentCombo;
		
		if (infoAlpha == 255)
		{
			comboCounter->setText(renderer, bebasBig, stringStream.str().c_str(), white);
			comboCounter->setBlendMode(SDL_BLENDMODE_BLEND);
		}

		if (song->isPlaying() && !isPaused)
		{
			if (infoAlpha - 3 < 0)
			{
				infoAlpha = 0;
			}
			else
			{
				infoAlpha -= 3;
			}
		}

		comboHeader->setAlpha(infoAlpha);
		if (currentCombo != 0)
			comboHeader->render(renderer, renderer->getMaxWidth() / 2 - comboHeader->getWidth() / 2, titlePanel->getHeight() - comboHeader->getHeight());
		
		comboCounter->setAlpha(infoAlpha);
		if (currentCombo != 0)
		{
			comboCounter->render(renderer, renderer->getMaxWidth() / 2 - comboCounter->getWidth() / 2, titlePanel->getHeight());
		}

		//Note Hit Alpha and logic
		if (!fadingIn)
		{
			stringStream.str("");
			switch (noteHitValue)
			{
			case PERFECT:
				stringStream << "perfect";
				break;
			case GOOD:
				stringStream << "good";
				break;
			case MISS:
				stringStream << "miss";
			case NO_INPUT:
				stringStream << " ";
			}

			if (noteHitAlpha == 255)
			{
				noteHit->setText(renderer, steelarBig, stringStream.str().c_str(), white);
				noteHit->setBlendMode(SDL_BLENDMODE_BLEND);
			}
			if (song->isPlaying() && !isPaused)
			{
				if (noteHitAlpha - 3 < 0)
				{
					noteHitAlpha = 0;
					noteHitValue = NO_INPUT;
				}
				else
				{
					noteHitAlpha -= 3;
				}

				noteHit->setAlpha(noteHitAlpha);

				if (noteHitValue != NO_INPUT)
				{
					noteHit->render(renderer, renderer->getMaxWidth() / 2 - noteHit->getWidth() / 2, renderer->getMaxHeight() - accuracyPanel->getHeight() - fret->getHeight() * 2);
				}
			}
		}
		else
		{
			noteHit->setAlpha(sceneAlpha);
			noteHit->render(renderer, renderer->getMaxWidth() / 2 - noteHit->getWidth() / 2, renderer->getMaxHeight() - accuracyPanel->getHeight() - fret->getHeight() * 2);
		}
		

		DButton->setAlpha(sceneAlpha);
		FButton->setAlpha(sceneAlpha);
		JButton->setAlpha(sceneAlpha);
		KButton->setAlpha(sceneAlpha);

		DButton->render(renderer, renderer->getMaxWidth() / 2 - fret->getWidth() * 3 / 8 - DButton->getWidth() / 2, renderer->getMaxHeight() - accuracyPanel->getHeight() / 2 - DButton->getHeight() / 2);
		FButton->render(renderer, renderer->getMaxWidth() / 2 - fret->getWidth() / 8 - FButton->getWidth() / 2, renderer->getMaxHeight() - accuracyPanel->getHeight() / 2 - FButton->getHeight() / 2);
		JButton->render(renderer, renderer->getMaxWidth() / 2 + fret->getWidth() / 4 - barHighlights->getWidth() / 2 - JButton->getWidth() / 2, renderer->getMaxHeight() - accuracyPanel->getHeight() / 2 - JButton->getHeight() / 2);
		KButton->render(renderer, renderer->getMaxWidth() / 2 + fret->getWidth() / 2 - barHighlights->getWidth() / 2 - KButton->getWidth() / 2, renderer->getMaxHeight() - accuracyPanel->getHeight() / 2 - KButton->getHeight() / 2);

		//Ticks
		oldBeat = currentBeat;
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

	int SongEasy::getAccuracy()
	{
		int noteAcc = 0;
		int humanDuration = songDurationTimer->getTicks();
		int diff = 0;
		if (humanDuration < 267)
		{
			diff = humanDuration;
		}
		else
		{
			diff = (int)fabsf(beatDuration - humanDuration);
		}
		
		if (diff <= 117)
		{
			noteAcc = PERFECT;
		}
		else if (diff > 177 && diff <= 267)
		{
			noteAcc = GOOD;
		}
		else if (diff > 267)
		{
			noteAcc = MISS;
		}

		return noteAcc;
	}

	bool SongEasy::isDone()
	{
		return done;
	}

	bool SongEasy::handleEvents(BINI::Events* events)
	{

		//Game Over Event
		if (beat > 356 || accuracy < 65.f)
		{
			if (sceneAlpha == 255)
			{
				std::cout << "Is Running" << "\n";

				//Store user results
				events->setUserData(score, maxCombo, "Easy", accuracy);

				if (accuracy < 65.f) {
					SoundFX::playGOLose();
				}
				if (beat > 356) {
					SoundFX::playGOSuccess();
				}

				//Sets next scene
				events->setState(BINI_GAME_OVER);


				timer->stop();
				songDurationTimer->stop();
				stepTimer->stop();
			}
		}

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
				infoAlpha = 255;

				switch (events->getKey())
				{
				case SDLK_d:

					if (isPaused)
						break;

					//Timing D
					dScoreQ = getAccuracy();

					bar1Highlight = 255;
					holdingD = true;
					break;
					

				case SDLK_f:

					if (isPaused)
						break;

					//Timing F
					fScoreQ = getAccuracy();

					holdingF = true;
					bar2Highlight = 255;
					break;

				case SDLK_j:

					if (isPaused)
						break;

					//Timing J
					jScoreQ = getAccuracy();

					holdingJ = true;
					bar3Highlight = 255;
					break;

				case SDLK_k:

					if (isPaused)
						break;

					//Timing K
					kScoreQ = getAccuracy();

					holdingK = true;
					bar4Highlight = 255;
					break;
				case SDLK_ESCAPE:
					if (!isPaused)
					{
						timer->pause();
						stepTimer->pause();
						song->pauseMusic();
						sceneAlpha = 50;
						isPaused = true;
					}
					else
					{
						timer->unpause();
						stepTimer->unpause();
						song->resumeMusic();
						sceneAlpha = 255;
						isPaused = false;
					}
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

//#include "SongEasy.h"
//
//namespace BINI
//{
//	SongEasy::SongEasy(BINI::Renderer* renderer)
//	{
//		//Textures
//		background = new BINI::Texture(renderer, "assets/Cover_Images/BINI_COVER_6.png");
//		overlay = new BINI::Texture(renderer, "assets/Cover_Images/SHADE.png");
//		titlePanel = new BINI::Texture(renderer, "assets/textures/GAMEPLAY_ASSETS/SONG_TITLE_HEADER.png");
//		accuracyPanel = new BINI::Texture(renderer, "assets/textures/GAMEPLAY_ASSETS/ACCURACY_HEADER.png");
//		noteTexture = new BINI::Texture(renderer, "assets/textures/GAMEPLAY_ASSETS/SINGLE_NOTE.png");
//
//		//Texture blend modes
//		background->setBlendMode(SDL_BLENDMODE_BLEND);
//		overlay->setBlendMode(SDL_BLENDMODE_BLEND);
//		titlePanel->setBlendMode(SDL_BLENDMODE_BLEND);
//		accuracyPanel->setBlendMode(SDL_BLENDMODE_BLEND);
//		noteTexture->setBlendMode(SDL_BLENDMODE_BLEND);
//
//		//Fonts and Labels
//		steelar = new BINI::Font("assets/fonts/Steelar-j9Vnj.ttf", 24);
//		bebas = new BINI::Font("assets/fonts/BebasNeue-Regular.ttf", 35);
//		SDL_Color black = { 0, 0 ,0 };
//		SDL_Color white = { 255, 255, 255 };
//		title = new BINI::Labels(renderer, steelar, "ISLANG PANTROPIKO", white);
//		bini = new BINI::Labels(renderer, bebas, "BINI", black);
//		title->setBlendMode(SDL_BLENDMODE_BLEND);
//		bini->setBlendMode(SDL_BLENDMODE_BLEND);
//
//		//Audio
//		song = new BINI::Music("assets/music/easy1.ogg");
//		sfx = new BINI::SoundFX("assets/sfx/metronome.wav");
//		
//		//Timer
//		timer = new BINI::Timer;
//		timer->stop();
//
//		//Parameters
//		done = false;
//		fadingIn = true;
//		sceneAlpha = 0;
//		beat = 1;
//		noteY = -noteTexture->getHeight();
//		noteYVelocity = renderer->getMaxHeight() / 208;
//		
//
//	}
//
//	SongEasy::~SongEasy()
//	{
//		//Cleanup
//
//		done = false;
//		fadingIn = true;
//		sceneAlpha = 0;
//
//		if (background != NULL)
//		{
//			delete background;
//			background = NULL;
//		}
//
//		if (overlay != NULL)
//		{
//			delete overlay;
//			overlay = NULL;
//		}
//
//		if (titlePanel != NULL)
//		{
//			delete titlePanel;
//			titlePanel = NULL;
//		}
//
//		if (song != NULL)
//		{
//			delete song;
//			song = NULL;
//		}
//
//		if (sfx != NULL)
//		{
//			delete sfx;
//			sfx = NULL;
//		}
//
//		if (timer != NULL)
//		{
//			delete timer;
//			timer = NULL;
//		}
//	}
//
//	void SongEasy::display(BINI::Renderer* renderer)
//	{
//
//		//Fade in;
//		if (fadingIn)
//		{
//			if (sceneAlpha + 1 > 255)
//			{
//				sceneAlpha = 255;
//				fadingIn = false;
//				timer->start();
//			}
//			else
//			{
//				sceneAlpha += 1;
//			}
//		}
//
//		//Fade out
//		if (!fadingIn && false)
//		{
//
//		}
//		
//		//Metronome
//		if (timer->getTicks() % 625 <= 16 && timer->isStarted() && timer->getTicks() > 625)
//		{
//			if (beat <= 8)
//				sfx->playSFX();
//		}
//
//		//Song controls
//		if (beat == 6)
//		{
//			song->startMusic(0);
//		}
//
//		//Set Texture Alphas
//		background->setAlpha(sceneAlpha);
//		overlay->setAlpha(sceneAlpha * 4 / 5);
//		titlePanel->setAlpha(sceneAlpha);
//		accuracyPanel->setAlpha(sceneAlpha);
//		noteTexture->setAlpha(sceneAlpha);
//		title->setAlpha(sceneAlpha);
//		bini->setAlpha(sceneAlpha);
//
//		//Render textures
//		background->render(renderer, 0, 0);
//		overlay->render(renderer, 0, 0);
//		titlePanel->render(renderer, 0, 0);
//		accuracyPanel->render(renderer, renderer->getMaxWidth() - accuracyPanel->getWidth(), renderer->getMaxHeight() - accuracyPanel->getHeight());
//		title->render(renderer, renderer->getMaxWidth() / 128, renderer->getMaxHeight() / 64);
//		bini->render(renderer, renderer->getMaxWidth() / 128, titlePanel->getHeight() - (bini->getHeight() * 5 / 2));
//		
//		if (beat >= 6 && noteY <= renderer->getMaxHeight() + noteTexture->getHeight()) 
//		{
//			noteTexture->render(renderer, (renderer->getMaxWidth() / 2) - noteTexture->getWidth(), noteY += (int)noteVelocity);
//		}
//					
//
//	}
//
//	bool SongEasy::isDone()
//	{
//		return done;
//	}
//
//	bool SongEasy::handleEvents(BINI::Events* events)
//	{
//		while (events->pollEvents() != 0)
//		{
//			//User exits
//			if (events->type() == SDL_QUIT)
//			{
//				return false;
//			}
//
//			//if key is pressed down
//			if (events->type() == SDL_KEYDOWN && !events->repeat())
//			{
//				switch (events->getKey())
//				{
//				case SDLK_DOWN:
//					
//					break;
//				}
//			}
//
//			//if key is released
//			if (events->type() == SDL_KEYUP && !events->repeat())
//			{
//				switch (events->getKey())
//				{
//				case SDLK_DOWN:
//					
//					break;
//				}
//			}
//		}
//
//		return true;
//	}
//}
