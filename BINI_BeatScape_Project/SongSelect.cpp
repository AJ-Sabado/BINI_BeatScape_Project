#include "SongSelect.h"

namespace BINI {

	SongSelect::SongSelect(Renderer* renderer) {
		done = false;

		//Initializing background slideshow
		initializeBackgrounds(renderer);

		//Initializing shade
		shade = new Texture(renderer, "assets/Cover_Images/SHADE.png");
	}

	void SongSelect::display(Renderer* renderer) {
		shade->render(renderer, 0, 0);
	}

	bool SongSelect::isDone() {
		return done;
	}

	bool SongSelect::handleEvents(Events* events){
		
		return true;
	}

	void SongSelect::initializeBackgrounds(Renderer* renderer) {
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
			backgrounds.push_back(new Background(renderer, path));
		}
	}

	void SongSelect::switchToNextSlide() {
		currentIndex = (currentIndex + 1) % backgrounds.size();
	}

}
