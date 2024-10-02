#include "MainMenu.h"

BINI::MainMenu::MainMenu(BINI::Renderer* renderer)
{
	menufont = new Font("assets/fonts/BebasNeue-Regular.ttf", 50);
	SDL_Color textColor = {0, 0, 0};
	start = new Labels(renderer, menufont, "Hello World", textColor);

	//ASSETS FOR BACKGROUND SLIDESHOW
	std::vector<std::string> paths = {
	"assets/Cover_Images/MAIN_MENU_EDIT/MAIN_MENU_COVER_1.png",
	"assets/Cover_Images/MAIN_MENU_EDIT/MAIN_MENU_COVER_2.png",
	"assets/Cover_Images/MAIN_MENU_EDIT/MAIN_MENU_COVER_3.png",
	"assets/Cover_Images/MAIN_MENU_EDIT/MAIN_MENU_COVER_4.png",
	"assets/Cover_Images/MAIN_MENU_EDIT/MAIN_MENU_COVER_5.png",
	"assets/Cover_Images/MAIN_MENU_EDIT/MAIN_MENU_COVER_6.png",
	"assets/Cover_Images/MAIN_MENU_EDIT/MAIN_MENU_COVER_7.png",
	"assets/Cover_Images/MAIN_MENU_EDIT/MAIN_MENU_COVER_8.png"
	};
	
	for (int i = 0; i < paths.size(); i++) {
		BINI::Background* temp = new BINI::Background(renderer, paths[i]);
		bBackground.push_back(temp);
	}
	
	//ASSETS FOR THE BASE
	baseTexture = new BINI::Texture(renderer, "assets/textures/HOME_PAGE_ASSET/HOME_BASE2.png");

	//ASSETS FOR LOGO
	biniBeatscapeLogo = new BINI::Texture(renderer, "assets/Logo/Bini_BeatScape_Logo_Resized.png");

	//SHADE Asset
	bg_shade = new BINI::Texture(renderer, "assets/Cover_Images/SHADE.png");
}

BINI::MainMenu::~MainMenu()
{
	if (!bBackground.empty())
	{
		bBackground.clear();
	}
}

void BINI::MainMenu::display(BINI::Renderer* renderer){
	
	//SLIDESHOW
	Uint32 now = SDL_GetTicks();  
	if (now - lastSwitchTime > slideDuration)
	{
		switchToNextSlide();
		lastSwitchTime = now;  
	}

	bBackground[currentIndex]->draw(renderer);

	//SHADE;
	bg_shade->render(renderer,0,0,NULL);

	//BASE
	baseTexture->render(renderer, 0, 0, NULL);

	//Logo
	SDL_Rect logo_rect;
	logo_rect.x = 0;
	logo_rect.y = 0;
	logo_rect.h = 750;
	logo_rect.w = 1125;
	biniBeatscapeLogo->render(renderer, 80, -78, &logo_rect);
	start->render(renderer, 0, 0 );
}

void BINI::MainMenu::switchToNextSlide()
{
	currentIndex++;
	if (currentIndex >= bBackground.size())
	{
		currentIndex = 0;
	}
}

