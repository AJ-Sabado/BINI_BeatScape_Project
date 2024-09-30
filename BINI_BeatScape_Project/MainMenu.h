#pragma once

#include "Scene.h"
#include "Background.h"
#include "Renderer.h"

namespace BINI
{
	class MainMenu : public BINI::Scene
	{
	public:

		MainMenu(BINI::Renderer* renderer);

		virtual void display(BINI::Renderer* renderer);

	private:

		BINI::Background* bBackground;
	};
}

