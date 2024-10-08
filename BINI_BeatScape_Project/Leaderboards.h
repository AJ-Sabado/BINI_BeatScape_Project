#pragma once

#include <memory>
#include <string>
#include "Scene.h"
#include "Background.h"
#include "Font.h"
#include "Labels.h"
#include "Renderer.h"
#include "Texture.h"
#include "ScoreContainer.h"
#include "sstream"
#include "iomanip"
#include "queue"
#include <vector>

namespace BINI {
	//Leaderboard Scene Class
	class Leaderboards : public Scene {
	public:
		//Constructor
		explicit Leaderboards(BINI::Renderer* renderer);
		
		//Destructor
		~Leaderboards() override ;

		//Inherited methods from Scene
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

		//LABELS
		Font* steelar;
		Font* steelarWhite;
		Font* bebasSmall;
		Font* bebasBig;
		Labels* lb_labels_1;
		Labels* lb_labels_2;
		Labels* lb_labels_3;
		SDL_Color black = { 0,0,0,255 };
		SDL_Color white = { 255,255,255,255 };

		const int lb_height = 50;

		//Selection
		int state = 1;

		//Scores
		BINI::ScoreContainer* scoreList = NULL;

		//Text stream
		std::stringstream textstream;

		bool done;

		int top3Diff = 186; //185
	};

}