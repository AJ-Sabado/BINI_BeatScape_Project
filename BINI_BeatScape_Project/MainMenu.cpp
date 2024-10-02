#include "MainMenu.h"
#include <SDL.h>

namespace BINI {

    MainMenu::MainMenu(Renderer* renderer) : menuFont(std::make_unique<Font>("assets/fonts/Steelar-j9Vnj.ttf", 28)) {
        SDL_Color textColor = { 0, 0, 0, 255 };
        startLabel = std::make_unique<Labels>(renderer, menuFont.get(), "START", textColor);
        leaderboardsLabel = std::make_unique<Labels>(renderer, menuFont.get(), "LEADERBOARDS", textColor);
        exitLabel = std::make_unique<Labels>(renderer, menuFont.get(), "EXIT", textColor);

        initializeBackgrounds(renderer);

        bgShade = std::make_unique<Texture>(renderer, "assets/Cover_Images/SHADE.png");
        baseTexture = std::make_unique<Texture>(renderer, "assets/textures/HOME_PAGE_ASSET/HOME_BASE2.png");
        biniBeatscapeLogo = std::make_unique<Texture>(renderer, "assets/Logo/Bini_BeatScape_Logo_Resized.png");
    }

    void MainMenu::initializeBackgrounds(Renderer* renderer) {
        const std::vector<std::string> paths = {
            "assets/Cover_Images/MAIN_MENU_EDIT/MAIN_MENU_COVER_1.png",
            "assets/Cover_Images/MAIN_MENU_EDIT/MAIN_MENU_COVER_2.png",
            "assets/Cover_Images/MAIN_MENU_EDIT/MAIN_MENU_COVER_3.png",
            "assets/Cover_Images/MAIN_MENU_EDIT/MAIN_MENU_COVER_4.png",
            "assets/Cover_Images/MAIN_MENU_EDIT/MAIN_MENU_COVER_5.png",
            "assets/Cover_Images/MAIN_MENU_EDIT/MAIN_MENU_COVER_6.png",
            "assets/Cover_Images/MAIN_MENU_EDIT/MAIN_MENU_COVER_7.png",
            "assets/Cover_Images/MAIN_MENU_EDIT/MAIN_MENU_COVER_8.png"
        };

        for (const auto& path : paths) {
            backgrounds.push_back(std::make_unique<Background>(renderer, path));
        }
    }

    void MainMenu::display(Renderer* renderer) {
        Uint32 now = SDL_GetTicks();
        if (now - lastSwitchTime > SLIDE_DURATION) {
            switchToNextSlide();
            lastSwitchTime = now;
        }

        backgrounds[currentIndex]->draw(renderer);
        bgShade->render(renderer, 0, 0, nullptr);
        baseTexture->render(renderer, 0, 0, nullptr);

        SDL_Rect logoRect = { 0, 0, 1125, 750 };
        biniBeatscapeLogo->render(renderer, 80, -78, &logoRect);

        startLabel->render(renderer, 584, 460);
        leaderboardsLabel->render(renderer, 513, 500);
        exitLabel->render(renderer, 600, 540);
    }

    void MainMenu::switchToNextSlide() {
        currentIndex = (currentIndex + 1) % backgrounds.size();
    }

}