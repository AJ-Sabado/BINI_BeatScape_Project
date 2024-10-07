#include "GameOver.h"

namespace BINI {
	GameOver::GameOver(Renderer* renderer) {
		done = false;

		initializeBackgrounds(renderer);

		//Initialize other things
		shade = new Texture(renderer, "assets/Cover_Images/SHADE.png");

		//Initializing assets
		box = new Texture(renderer, "assets/textures/GAME_OVER/Game_Over_With_Box.png");
		enter = new Texture(renderer, "assets/textures/GAME_OVER/Press_Enter.png");
		name = new Texture(renderer, "assets/textures/GAME_OVER/3_Letter_Name.png");
		labels = new Texture(renderer, "assets/textures/GAME_OVER/Game_Over_Label.png");

		// Initialize font
		steelar = new Font("assets/fonts/Steelar-j9Vnj.ttf", 150);

		// Initialize Labels
		letter_1 = new Labels(renderer, steelar, "", textColorWhite);
		letter_2 = new Labels(renderer, steelar, "", textColorWhite);
		letter_3 = new Labels(renderer, steelar, "", textColorWhite);

	}

	GameOver::~GameOver() {
		delete shade;
		delete box;
		delete enter;
		delete name;
		delete labels;

		// Delete label objects
		delete letter_1;
		delete letter_2;
		delete letter_3;

		// Delete background objects
		for (auto background : backgrounds) {
			delete background;
		}

		// Clear the backgrounds vector (optional, for safety)
		backgrounds.clear();
	}

	void GameOver::display(Renderer* renderer) {
		Uint32 now = SDL_GetTicks();
		if (now - lastSwitchTime > SLIDE_DURATION) {
			switchToNextSlide();
			lastSwitchTime = now;
		}

		backgrounds[currentIndex]->draw(renderer);
		shade->render(renderer, 0, 0, nullptr);

		box->render(renderer,0,0,nullptr);
		enter->render(renderer, 0, 0, nullptr);
		name->render(renderer, 0, 0, nullptr);
		labels->render(renderer, 0, 0, nullptr);

		if (letters.size() > 0) {
			letter_1->setText(renderer, steelar, letters[0], textColorWhite);
			letter_1->render(renderer, 345, 380, nullptr);
		}
		if (letters.size() > 1) {
			letter_2->setText(renderer, steelar, letters[1], textColorWhite);
			letter_2->render(renderer, 565, 380, nullptr);
		}
		if (letters.size() > 2) {
			letter_3->setText(renderer, steelar, letters[2], textColorWhite);
			letter_3->render(renderer, 785, 380, nullptr);
		}

	}

	bool GameOver::isDone() {
		
		return done;
	}

	bool GameOver::handleEvents(Events* events) {
		while (events->pollEvents() != 0)
		{
			if (done)
			{
				std::cout << "Yes" << "\n";
				for (std::string a : letters)
				{
					player_name += a;
				}
				std::cout << player_name.c_str() << "\n";
			}

			//User exits
			if (events->type() == SDL_QUIT)
			{
				return false;
			}
			if (events->type() == SDL_KEYDOWN && !events->repeat())
			{
				switch (events->getKey())
				{
				case SDLK_a: case SDLK_b: case SDLK_c: case SDLK_d: case SDLK_e:
				case SDLK_f: case SDLK_g: case SDLK_h: case SDLK_i: case SDLK_j:
				case SDLK_k: case SDLK_l: case SDLK_m: case SDLK_n: case SDLK_o:
				case SDLK_p: case SDLK_q: case SDLK_r: case SDLK_s: case SDLK_t:
				case SDLK_u: case SDLK_v: case SDLK_w: case SDLK_x: case SDLK_y:
				case SDLK_z:
				case SDLK_0: case SDLK_1: case SDLK_2: case SDLK_3: case SDLK_4:
				case SDLK_5: case SDLK_6: case SDLK_7: case SDLK_8: case SDLK_9:
					if (letters.size() < 3) {
						// Convert the key to its corresponding character
						char inputChar = events->getKey() < SDLK_0 ? events->getKey() - SDLK_a + 'a' : events->getKey() - SDLK_0 + '0';
						letters.push_back(std::string(1, inputChar));
					}
					for (int i = 0; i < letters.size(); i++) {
						std::cout << letters[i] << std::endl;
					}
					SoundFX::playSlideSFX();
					break;
				case SDLK_BACKSPACE:
					SoundFX::playSlideSFX();
					letters.pop_back();
					break;
				case SDLK_RETURN:
					SoundFX::playEnterSFX();
					if (letters.size() < 3) {
						continue;
					}
					for (std::string a : letters)
					{
						player_name += a;
					}
					events->setUserInitials(player_name);
					events->exportData();
					events->setState(BINI_START);
					done = true;
					break;
				}
			}
		}
		return true;
	}

	void GameOver::switchToNextSlide() {
		currentIndex = (currentIndex + 1) % backgrounds.size();
	}

	void GameOver::initializeBackgrounds(Renderer* renderer) {
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

}