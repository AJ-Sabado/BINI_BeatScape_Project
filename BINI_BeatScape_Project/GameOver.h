#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Scene.h"
#include "Background.h"
#include "Font.h"
#include "Labels.h"
#include "Renderer.h"
#include "Texture.h"
#include "Music.h"

namespace BINI {
	class GameOver : public Scene{
	public:
		GameOver(Renderer* renderer);
		~GameOver();

		virtual void display(Renderer* renderer);

		virtual bool isDone();

		virtual bool handleEvents(BINI::Events* events);

	private:
		bool done;

		//BG SLIDESHOW
		void switchToNextSlide();
		void initializeBackgrounds(Renderer* renderer);
		std::vector<Background*> backgrounds;
		size_t currentIndex{ 0 };
		Uint32 lastSwitchTime{ 0 };
		static constexpr int SLIDE_DURATION{ 5000 };
		Texture* shade;

		//GameOver UI Assets
		Texture* box;
		Texture* name;
		Texture* enter;
		Texture* labels;

		//3 letter name
		std::vector<std::string> letters;
		std::string player_name;

		//Letter Label assets
		Font* steelar;
		SDL_Color textColorWhite = { 255, 255, 255 , 255 };
		Labels* letter_1;
		Labels* letter_2;
		Labels* letter_3;
};
}