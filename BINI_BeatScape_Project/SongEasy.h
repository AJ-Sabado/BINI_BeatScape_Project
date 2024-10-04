#pragma once

#include "queue"
#include "Scene.h"
#include "Renderer.h"
#include "Timer.h"
#include "Events.h"
#include "Music.h"
#include "Texture.h"
#include "Font.h"
#include "Labels.h"

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

		//Textures
		BINI::Texture* background;

		BINI::Texture* overlay;

		BINI::Texture* titlePanel;

		BINI::Texture* accuracyPanel;

		BINI::Texture* noteTexture;

		BINI::Music* song;

		BINI::Timer* timer;

		BINI::SoundFX* sfx;


		//Fonts
		BINI::Font* steelar;
		BINI::Font* bebas;

		//Labels
		BINI::Labels* title;
		BINI::Labels* bini;


		//Other Class Variables

		bool done;
		
		Uint8 sceneAlpha;

		bool fadingIn;

		int beat;

		int noteY;		//Temp
	};
}


