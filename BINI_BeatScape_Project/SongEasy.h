#pragma once

#include "Scene.h"
#include "Renderer.h"
#include "Timer.h"
#include "Events.h"
#include "Music.h"
#include "Texture.h"

namespace BINI
{
	class SongEasy : public BINI::Scene
	{
	public:
		SongEasy(BINI::Renderer* renderer);

		~SongEasy();

		void display(BINI::Renderer* renderer);

		bool isDone();

		bool handleEvents(BINI::Events* events);

	private:

		BINI::Texture* background;

		BINI::Texture* overlay;

		BINI::Texture* titlePanel;

		BINI::Texture* accuracyPanel;

		BINI::Texture* noteTexture;

		BINI::Music* song;

		BINI::Timer* timer;

		BINI::SoundFX* sfx;

		bool done;
		
		Uint8 sceneAlpha;

		bool fadingIn;

		int beat;

		int noteY;

	};
}


