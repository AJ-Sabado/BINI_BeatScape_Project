#include "MainMenu.h"

BINI::MainMenu::MainMenu(BINI::Renderer* renderer)
{
	bBackground = new BINI::Background(renderer, "assets/textures/HOME_PAGE_ASSET/HOME_PAGE_MOCKUP.png");
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
}