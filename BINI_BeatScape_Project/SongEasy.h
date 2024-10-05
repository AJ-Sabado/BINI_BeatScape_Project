#pragma once

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

		//List of current bars to be rendererd
		
		std::vector<BINI::SongBar*> currentBars;
		std::queue<BINI::SongBar*> chart;
		std::vector<BINI::SongBar*>::iterator bar;

		int NOTE_POS1;
		int NOTE_POS2;
		int NOTE_POS3;
		int NOTE_POS4;

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

		BINI::Music* song;

		BINI::Timer* timer;

		BINI::Timer* stepTimer;

		BINI::SoundFX* sfx;

		BINI::ChartReader* chartReader;

		//Rects
		SDL_Rect basebarSize;

		//Fonts
		BINI::Font* steelar;
		BINI::Font* bebas;

		//Labels
		BINI::Labels* title;
		BINI::Labels* bini;


		//Other Class Variables

		bool done;
		
		Uint8 sceneAlpha;

		Uint8 bar1Highlight;
		Uint8 bar2Highlight;
		Uint8 bar3Highlight;
		Uint8 bar4Highlight;


		bool fadingIn;

		int beat;

		//Private Methods
		Uint8 barHighlightsfadeOut(Uint8 highlight);
	};
}


