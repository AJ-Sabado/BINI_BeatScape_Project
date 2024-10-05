#include "Leaderboards.h"

namespace BINI {

	Leaderboards::Leaderboards(Renderer* renderer) {
		done = false;

		//Initializing background slideshow
		initializeBackgrounds(renderer);

		//Initializing shade
		shade = new Texture(renderer, "assets/Cover_Images/SHADE.png");

		//Initializing textures
		LB_Header = new Texture(renderer, "assets/textures/LEADERBOARDS_ASSET/LB_HEADER_FS.png");
		Top_1 = new Texture(renderer, "assets/textures/LEADERBOARDS_ASSET/LB_TOP_1.png");
		Top_2 = new Texture(renderer, "assets/textures/LEADERBOARDS_ASSET/LB_TOP_2.png");
		Top_3 = new Texture(renderer, "assets/textures/LEADERBOARDS_ASSET/LB_TOP_3.png");
		LB_Main = new Texture(renderer, "assets/textures/LEADERBOARDS_ASSET/LB_MAIN_FS.png");

	}

	void Leaderboards::display(Renderer* renderer) {
		Uint32 now = SDL_GetTicks();
		if (now - lastSwitchTime > SLIDE_DURATION) {
			switchToNextSlide();
			lastSwitchTime = now;
		}

		backgrounds[currentIndex]->draw(renderer);
		shade->render(renderer, 0, 0, nullptr);

		//Displaying Texture Assets
		LB_Header->render(renderer, 0, 0, nullptr);
		Top_1->render(renderer, 0, 0, nullptr);
		Top_2->render(renderer, 0, 0, nullptr);
		Top_3->render(renderer, 0, 0, nullptr);
		LB_Main->render(renderer, 0, 0, nullptr);

	}

	bool Leaderboards::isDone() {
		return done;
	}

	bool Leaderboards::handleEvents(Events* events){
		while (events->pollEvents() != 0)
		{
			//User exits
			if (events->type() == SDL_QUIT)
			{
				return false;
			}

			
		}
		return true;
	}

	void Leaderboards::initializeBackgrounds(Renderer* renderer) {
		const std::vector<std::string> paths = {
			"assets/Cover_Images/BINI_COVER_1.png",
			"assets/Cover_Images/BINI_COVER_2.png",
			"assets/Cover_Images/BINI_COVER_3.png",
			"assets/Cover_Images/BINI_COVER_4.png",
			"assets/Cover_Images/BINI_COVER_5.png",
			"assets/Cover_Images/BINI_COVER_6.png",
			"assets/Cover_Images/BINI_COVER_7.png",
			"assets/Cover_Images/BINI_COVER_8.png"
		};

		for (const auto& path : paths) {
			backgrounds.push_back(new Background(renderer, path));
		}
	}

	void Leaderboards::switchToNextSlide() {
		currentIndex = (currentIndex + 1) % backgrounds.size();
	}


}
