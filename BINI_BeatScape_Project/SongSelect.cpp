#include "SongSelect.h"

namespace BINI {

	SongSelect::SongSelect(Renderer* renderer) {
		done = false;

		//Initializing background slideshow
		initializeBackgrounds(renderer);

		//Initializing shade
		shade = new Texture(renderer, "assets/Cover_Images/SHADE.png");

		//Initializing textures
		header = new Texture(renderer, "assets/textures/SONG_SELECT/SONG SELECT ASSETS IN PNG/HEADER_FS.png");
		pantropiko_easy = new Texture(renderer, "assets/textures/SONG_SELECT/SONG SELECT ASSETS IN PNG/PANTROPIKO_FS.png");
		salamin_mid = new Texture(renderer, "assets/textures/SONG_SELECT/SONG SELECT ASSETS IN PNG/SALAMIN_FS.png");
		cherry_hard = new Texture(renderer, "assets/textures/SONG_SELECT/SONG SELECT ASSETS IN PNG/CHERRY_FS.png");
	}

	void SongSelect::display(Renderer* renderer) {
		Uint32 now = SDL_GetTicks();
		if (now - lastSwitchTime > SLIDE_DURATION) {
			switchToNextSlide();
			lastSwitchTime = now;
		}

		backgrounds[currentIndex]->draw(renderer);
		shade->render(renderer, 0, 0, nullptr);

		header->render(renderer, 0, 0, nullptr);

		switch (state) {
		case 1: 
			pantropiko_easy->render(renderer, 0,0, nullptr);
			break;
		case 2: // Enlarge salamin_mid
			salamin_mid->render(renderer, 0,0, nullptr);
			break;
		case 3: // Enlarge cherry_hard
			cherry_hard->render(renderer, 0,0, nullptr);
			break;
		default:
			break;
		}

		// Render other textures if needed
		if (state != 1) {
			pantropiko_easy->render(renderer, -100,0, nullptr);
		}
		if (state != 2) {
			salamin_mid->render(renderer, -100,0, nullptr);
		}
		if (state != 3) {
			cherry_hard->render(renderer, -100,0, nullptr);
		}
	}

	bool SongSelect::isDone() {
		return done;
	}

	bool SongSelect::handleEvents(Events* events){
		while (events->pollEvents() != 0)
		{
			//User exits
			if (events->type() == SDL_QUIT)
			{
				return false;
			}

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
					switch (state) {
					case 1:
						events->setState(BINI_SONG_EASY);
						break;
					case 2:
						events->setState(BINI_SONG_MEDIUM);
						break;
					case 3:
						events->setState(BINI_SONG_HARD);
						break;
					}
					Music::fadeOutMusic(1000);
					done = true;
					break;
				case SDLK_ESCAPE:
					SoundFX::playEnterSFX();
					events->setState(BINI_START);
					done = true;
					break;
				}
			}
		}
		return true;
	}

	void SongSelect::initializeBackgrounds(Renderer* renderer) {
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

	void SongSelect::switchToNextSlide() {
		currentIndex = (currentIndex + 1) % backgrounds.size();
	}

}
