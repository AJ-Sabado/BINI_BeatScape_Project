#include "MainMenu.h"
#include <SDL.h>

namespace BINI {

    MainMenu::MainMenu(Renderer* renderer){
        done = false;

        //Initializing BG Music
        bgMusic = new Music("assets/music/Menu/Salamin_Rock.mp3");

        //LABELS AND FONT DECLARATIONS
        menuFont = new Font("assets/fonts/Steelar-j9Vnj.ttf", 28);
        textColorWhite = { 255, 255, 255 , 255 };
        startLabel = new Labels(renderer, menuFont, "START", textColorWhite);
        leaderboardsLabel = new Labels(renderer, menuFont, "LEADERBOARDS", textColorWhite);
        exitLabel = new Labels(renderer, menuFont, "EXIT", textColorWhite);

        //INITIALIZING BG-SLIDESHOW TEXTURES
        initializeBackgrounds(renderer);

        //INITIALIZING MAIN TEXTURES FOR UI
        bgShade = std::make_unique<Texture>(renderer, "assets/Cover_Images/SHADE.png"); //GRADIENT SHADE
        baseTexture = std::make_unique<Texture>(renderer, "assets/textures/HOME_PAGE_ASSET/HOME_BASE2.png"); //STAGE
        biniBeatscapeLogo = std::make_unique<Texture>(renderer, "assets/Logo/Bini_BeatScape_Logo_Resized.png"); //LOGO
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

        //Playing bg Music
        bgMusic->startMusic(9999);

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

        switch (state) {
        case 1:
            startLabel->setColor(255, 255, 255);
            leaderboardsLabel->setColor(0, 0, 0);
            exitLabel->setColor(0, 0, 0);
            break;
        case 2:
            startLabel->setColor(0, 0, 0);
            leaderboardsLabel->setColor(255, 255, 255);
            exitLabel->setColor(0, 0, 0);
            break;
        case 3:
            startLabel->setColor(0, 0, 0);
            leaderboardsLabel->setColor(0, 0, 0);
            exitLabel->setColor(255, 255, 255);
            break;
        }

        startLabel->render(renderer, 584, 460);
        leaderboardsLabel->render(renderer, 513, 500);
        exitLabel->render(renderer, 600, 540);
    }

    void MainMenu::switchToNextSlide() {
        currentIndex = (currentIndex + 1) % backgrounds.size();
    }

    //Returns done var which signifies this scene is ready to exit/transition
    bool MainMenu::isDone()
    {
        return done;
    }

    //Handle events here
    bool MainMenu::handleEvents(BINI::Events* events)
    {

        while (events->pollEvents() != 0)
        {
            //User exits
            if (events->type() == SDL_QUIT)
            {
                return false;
            }

            //if key is pressed down
            if (events->type() == SDL_KEYDOWN && !events->repeat())
            {
                switch (events->getKey())
                {
                case SDLK_DOWN:
                    state++;
                    if (state > 3) // Adjust based on number of menu items
                    {
                        state = 1; // Loop back to the first menu option
                    }
                    std::cout << "Down key pressed. Current choice: " << state << "\n";
                    SoundFX::playSlideSFX();
                    break;
                case SDLK_UP:
                    state--;
                    if (state < 1) // Loop back to the last menu option
                    {
                        state = 3; // Adjust based on number of menu items
                    }
                    std::cout << "Up key pressed. Current choice: " << state << "\n";
                    SoundFX::playSlideSFX();
                    break;
                case SDLK_RETURN:
                    SoundFX::playEnterSFX();
                    break;
                }
            }

            //if key is released
            if (events->type() == SDL_KEYUP && !events->repeat())
            {
                switch (events->getKey())
                {
                case SDLK_DOWN:
                    std::cout << "Down key released.\n";
                    break;
                }
            }
        }

        return true;
    }
}