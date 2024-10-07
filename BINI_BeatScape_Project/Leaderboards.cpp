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

		//LABELS AND FONTS
		steelar = new Font("assets/fonts/Steelar-j9Vnj.ttf", 40);
		bebasSmall = new Font("assets/fonts/BebasNeue-Regular.ttf", 39);
		bebasBig = new Font("assets/fonts/BebasNeue-Regular.ttf", 49);

		lb_labels_1 = new Labels(renderer, steelar, "", black);
		lb_labels_2 = new Labels(renderer, bebasSmall, "", white);
		lb_labels_3 = new Labels(renderer, bebasBig, "", white);
	}

	Leaderboards::~Leaderboards() {
		delete shade;
		delete LB_Header;
		delete Top_1;
		delete Top_2;
		delete Top_3;
		delete LB_Main;

		for (auto background : backgrounds) {
			delete background;
		}
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

		//DISPLAYING TOP 3 LABELS
		lb_labels_1->setText(renderer, steelar, "AAA - 00000", black);
		lb_labels_2->setText(renderer, bebasSmall, "----", white);
		lb_labels_3->setText(renderer, bebasBig, "----", white);

		BINI::ScoreContainer* current = scoreList;


		

		
		
		//TOP 1 - 3
		for (int i = 0; i < 3; i++)
		{
			if (current != NULL)
			{
				textstream.str("");
				textstream << current->userInitials << " - " << current->score;
				lb_labels_1->setText(renderer, steelar, textstream.str().c_str(), black);
				lb_labels_1->render(renderer, 155, 180 + i * top3Diff);

				textstream.str("");
				textstream << current->userDifficulty;
				lb_labels_2->setText(renderer, bebasSmall, textstream.str().c_str(), white);
				lb_labels_2->render(renderer, 240, 234 + i * top3Diff);

				textstream.str("");
				textstream << std::fixed << std::setprecision(2) << current->accuracy << "%";
				lb_labels_2->setText(renderer, bebasSmall, textstream.str().c_str(), white);
				lb_labels_2->render(renderer, 400, 234 + i * top3Diff);

				textstream.str("");
				textstream << current->maxCombo;
				lb_labels_3->setText(renderer, bebasSmall, textstream.str().c_str(), white);
				lb_labels_3->render(renderer, 270, 266 + i * top3Diff);
				current = current->next;
			}
			else
			{
				lb_labels_1->setText(renderer, steelar, "AAA - 00000", black);
				lb_labels_2->setText(renderer, bebasSmall, "----", white);
				lb_labels_3->setText(renderer, bebasBig, "----", white);

				lb_labels_1->render(renderer, 155, 180 + i * top3Diff);
				lb_labels_2->render(renderer, 240, 234 + i * top3Diff);
				lb_labels_2->render(renderer, 400, 234 + i * top3Diff);
				lb_labels_3->render(renderer, 270, 266 + i * top3Diff);

			}
			
			
			
			
		}
		

		
		for (int i = 0; i <= 10; i++) {

			if (current != NULL)
			{
				textstream.str("");
				textstream << current->userInitials << " - " << current->userDifficulty << " - " << current->score;
				lb_labels_1->setText(renderer, steelar, textstream.str().c_str(), white);
				current = current->next;
			}
			else
			{
				lb_labels_1->setText(renderer, steelar, "AAA - **** - 00000", white);
			}

			lb_labels_1->render(renderer, 685, 100+(i*lb_height));
		}
	}

	bool Leaderboards::isDone() {
		return done;
	}

	bool Leaderboards::handleEvents(Events* events) {
		while (events->pollEvents() != 0)
		{

			//Load Scores
			if (events->getScoreList() != NULL && scoreList == NULL)
			{
				std::cout << "Once\n";
				scoreList = events->getScoreList();
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

		void Leaderboards::initializeBackgrounds(Renderer * renderer) {
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
	
