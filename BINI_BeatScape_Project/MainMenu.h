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

namespace BINI {

    class MainMenu : public Scene {
    public:
        explicit MainMenu(Renderer* renderer);
        ~MainMenu() override = default;

        MainMenu(const MainMenu&) = delete;
        MainMenu& operator=(const MainMenu&) = delete;
        MainMenu(MainMenu&&) = delete;
        MainMenu& operator=(MainMenu&&) = delete;

        void display(Renderer* renderer) override;

    private:
        void switchToNextSlide();
        void initializeBackgrounds(Renderer* renderer);

        std::unique_ptr<Font> menuFont;
        std::unique_ptr<Labels> startLabel;
        std::unique_ptr<Labels> leaderboardsLabel;
        std::unique_ptr<Labels> exitLabel;

        std::vector<std::unique_ptr<Background>> backgrounds;
        size_t currentIndex{ 0 };
        Uint32 lastSwitchTime{ 0 };
        static constexpr int SLIDE_DURATION{ 5000 };

        std::unique_ptr<Texture> bgShade;
        std::unique_ptr<Texture> baseTexture;
        std::unique_ptr<Texture> biniBeatscapeLogo;
    };

}