#pragma once

#include <vector>
#include <chrono>

#include "Scene.h"
#include "Background.h"
#include "Font.h"
#include "Labels.h"
#include "Renderer.h"

namespace BINI
{
	//Main menu scene wrapper.
	class MainMenu : public BINI::Scene
	{
	public:

		//Main menu constructor.
		MainMenu(BINI::Renderer* renderer);

		//Main menu deconstructor.
		~MainMenu();

		virtual void display(BINI::Renderer* renderer);

		//virtual bool exitScene(BINI::Renderer* renderer);

	private:
		BINI::Font* menufont;
		BINI::Labels* start;

		//BACKGROUND ASPECT
		std::vector<BINI::Background*> bBackground;
		int currentIndex;
		Uint32 lastSwitchTime;
		const int slideDuration = 5000;
		void switchToNextSlide();

		//BG FOREGROUND SHADE
		BINI::Texture* bg_shade;

		//BASE
		BINI::Texture* baseTexture;

		//LOGO
		BINI::Texture* biniBeatscapeLogo;

	};
}

