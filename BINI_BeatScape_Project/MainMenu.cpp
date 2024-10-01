#include "MainMenu.h"

BINI::MainMenu::MainMenu(BINI::Renderer* renderer)
{
	bBackground = new BINI::Background(renderer, "assets/textures/HOME_PAGE_ASSET/HOME_PAGE_MOCKUP.png");
	menufont = new Font("assets/fonts/BebasNeue-Regular.ttf", 28);
	SDL_Color textColor = {0, 0, 0};
	start = new Labels(renderer, menufont, "Start hehehe", textColor);
}

BINI::MainMenu::~MainMenu()
{
	if (bBackground != NULL)
	{
		delete bBackground;
		bBackground = NULL;
	}
}

void BINI::MainMenu::display(BINI::Renderer* renderer)
{
	bBackground->draw(renderer);
	start->render(renderer, 0, 0);
}