#pragma once

#include <memory>
#include <string>
#include "Scene.h"
#include "Background.h"
#include "Font.h"
#include "Labels.h"
#include "Renderer.h"
#include "Texture.h"
#include <vector>

namespace BINI {

	class Leaderboards : public Scene {
	public:
		explicit Leaderboards(BINI::Renderer* renderer);
		~Leaderboards() override = default;

		void display(BINI::Renderer* renderer) override;
		bool isDone() override;
		bool handleEvents(BINI::Events* events) override;

	private:
		//BACKGROUND ASPECT
		void switchToNextSlide();
		void initializeBackgrounds(BINI::Renderer* renderer);
		size_t currentIndex{ 0 };
		Uint32 lastSwitchTime{ 0 };
		static constexpr int SLIDE_DURATION{ 5000 };
		std::vector<Background*> backgrounds;
		Texture* shade;


		//Textures
		Texture* LB_Header;
		Texture* Top_1;
		Texture* Top_2;
		Texture* Top_3;
		Texture* LB_Main;

		//Selection
		int state = 1;

		bool done;
	};

}