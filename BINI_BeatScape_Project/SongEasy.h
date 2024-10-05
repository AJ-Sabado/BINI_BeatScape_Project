#pragma once

#include <chrono>

#include "Scene.h"
#include "Renderer.h"
#include "Timer.h"
#include "Events.h"
#include "Music.h"
#include "Texture.h"
#include "Font.h"
#include "Labels.h"
#include "SongBar.h"
#include "ChartReader.h"
#include "vector"
#include "queue"
#include "sstream"
#include "iomanip"

namespace BINI
{
	class SongEasy : public BINI::Scene
	{
	public:
		//Constructor
		SongEasy(BINI::Renderer* renderer);

		//Destructor
		~SongEasy();

		//Display elements
		void display(BINI::Renderer* renderer);

		//Returns true if current scene is done
		bool isDone();

		//Handle key events
		bool handleEvents(BINI::Events* events);

	private:

		//Parameters
		float noteYVelocity;
		int score = 0;
		const int maxNotes = 235;
		const int maxScore = 500000;
		int perfectNotes = maxNotes;

		//Scores
		float accuracy = 100.f;
		int dScoreQ = 0;
		int fScoreQ = 0;
		int jScoreQ = 0;
		int kScoreQ = 0;
		int totalScore = 0;
		int maxCombo = 0;
		int currentCombo = 0;

		//List of current bars to be rendered
		std::vector<BINI::SongBar*> currentBars;
		std::queue<BINI::SongBar*> chart;
		std::vector<BINI::SongBar*>::iterator bar;

		//note positions
		int NOTE_POS1;
		int NOTE_POS2;
		int NOTE_POS3;
		int NOTE_POS4;

		//Key event flags
		bool holdingD;
		bool holdingF;
		bool holdingJ;
		bool holdingK;

		//Textures
		BINI::Texture* background;
		BINI::Texture* overlay;
		BINI::Texture* titlePanel;
		BINI::Texture* accuracyPanel;
		BINI::Texture* basebar;
		BINI::Texture* barHighlights;
		BINI::Texture* fret;
		BINI::Texture* noteTexture;

		//Music
		BINI::Music* song;

		//SFX
		BINI::SoundFX* sfx;

		//Timers
		BINI::Timer* timer;
		BINI::Timer* stepTimer;
		BINI::Timer* beatDurationTimer;

		//Chart reader
		BINI::ChartReader* chartReader;

		//Rects
		SDL_Rect basebarSize;

		//Fonts
		BINI::Font* steelar;
		BINI::Font* bebas;
		BINI::Font* steelarBig;
		BINI::Font* bebasBig;

		//Colors
		SDL_Color black;
		SDL_Color white;

		//Labels
		BINI::Labels* title;
		BINI::Labels* bini;
		BINI::Labels* accuracyLabel;
		BINI::Labels* scoreLabel;
		BINI::Labels* comboHeader;
		BINI::Labels* comboCounter;
		BINI::Labels* noteHit;

		//Text stream
		std::stringstream stringStream;

			//Other Class Variables

		//flags
		bool done;
		bool fadingIn;
		bool isPaused;
		int noteHitValue;

		//scene opacity modifier
		Uint8 sceneAlpha;

		//note bar highlights modifier
		Uint8 bar1Highlight;
		Uint8 bar2Highlight;
		Uint8 bar3Highlight;
		Uint8 bar4Highlight;
		Uint8 infoAlpha;
		Uint8 noteHitAlpha;

		//Metronome Calc
		int beat;
		int oldBeat;
		int currentBeat;
		float bps;

		//Beat detection
		Uint8 beatDuration;
		Uint8 humanDuration;

		//Private Methods
		Uint8 barHighlightsfadeOut(Uint8 highlight);
		int getAccuracy();
	};
}


