
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

    class MainMenu : public Scene {
    public:
        explicit MainMenu(Renderer* renderer);
        ~MainMenu();

        MainMenu(const MainMenu&) = delete;
        MainMenu& operator=(const MainMenu&) = delete;
        MainMenu(MainMenu&&) = delete;
        MainMenu& operator=(MainMenu&&) = delete;

        //Inherited Scene functions  *refer to Scene class for more info.
        void display(Renderer* renderer) override;
        bool isDone() override;
        bool handleEvents(BINI::Events* events) override;

    private:
        //FUNCTIONS
        void switchToNextSlide();
        void initializeBackgrounds(Renderer* renderer);

        //LABELS
        Font* menuFont;
        int state = 1;
        SDL_Color textColorWhite;
        Labels* startLabel;
        Labels* leaderboardsLabel;
        Labels* exitLabel;

        //MENU BG SLIDESHOW
        std::vector<std::unique_ptr<Background>> backgrounds;
        size_t currentIndex{ 0 };
        Uint32 lastSwitchTime{ 0 };
        static constexpr int SLIDE_DURATION{ 5000 };

        //MENU UI TEXTURES
        std::unique_ptr<Texture> bgShade;
        std::unique_ptr<Texture> baseTexture;
        std::unique_ptr<Texture> biniBeatscapeLogo;

        //BG Music
        Music* bgMusic;


        //Change to true if your scene is ready to exit/transition
        bool done;
    };

}
