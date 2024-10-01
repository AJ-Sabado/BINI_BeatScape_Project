#pragma once

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

		BINI::Background* bBackground;
		BINI::Font* menufont;
		BINI::Labels* start;
	};
}

