#include "CompanyLogo.h"
#include <SDL.h>


namespace BINI {

	CompanyLogo::CompanyLogo(Renderer* renderer) {

		steelar = new Font("assets/fonts/Steelar-j9Vnj.ttf", 28);
		bebas = new Font("assets/fonts/BebasNeue-Regular.ttf", 30);
		SDL_Color white = { 255,255,255,255 };
		pressStart = new Labels(renderer, steelar, "<PRESS ENTER TO START>", white);
		instruction = new Labels(renderer, bebas, "[!] READ: This game uses keyboard only. Enjoy!", white);
		
		background = new Texture(renderer, "assets/Logo/Black_BG.png");
		logo = new Texture(renderer, "assets/Logo/Company_Logo_Asset.png");

		startTimeFadeIn = SDL_GetTicks();
		startTimeFadeOut = 0;
	}

	CompanyLogo::~CompanyLogo() {
		delete background;
		delete logo;
	}

	void CompanyLogo::display(Renderer* renderer) {

		background->render(renderer, 0, 0);
		switch (enter) {
		case 0:
			fade_in();
			logo->setAlpha(opacity);
			logo->render(renderer, 0, 0);
			pressStart->setAlpha(opacity);
			pressStart->render(renderer, 420, 600);
			instruction->setAlpha(opacity);
			instruction->render(renderer, 470, 626);
			break;
		case 1:
			fade_out();
			logo->setAlpha(opacity);
			logo->render(renderer, 0, 0);
			pressStart->setAlpha(opacity);
			pressStart->render(renderer, 420, 600);
			instruction->setAlpha(opacity);
			instruction->render(renderer, 470, 626);
			break;
		}
	}


	bool CompanyLogo::isDone() {
		return done;
	}

	bool CompanyLogo::handleEvents(BINI::Events* events) {

		if (done)
		{
			events->setState(BINI_START);
		}

		while (events->pollEvents() != 0) {
			// Handle events
			if (events->type() == SDL_QUIT)
			{
				return false;
			}

			if (events->type() == SDL_KEYDOWN && !events->repeat())
			{
				switch (events->getKey())
				{
				case SDLK_RETURN:
					enter = 1;
					startTimeFadeOut = SDL_GetTicks();
					break;
				}
			}
		}
		return true;
	}

	void CompanyLogo::fade_in() {
		Uint32 currentTime = SDL_GetTicks();
		Uint32 elapsedTime = currentTime - startTimeFadeIn;

		// Fade in over 1 seconds (2000 milliseconds)
		const Uint32 fadeDuration = 1000;

		if (elapsedTime < fadeDuration) {
			float progress = static_cast<float>(elapsedTime) / fadeDuration;
			opacity = static_cast<Uint8>(255 * progress);
		}
		else {
			opacity = 255;
			done = true;
		}
	}

	void CompanyLogo::fade_out() {
		Uint32 currentTime = SDL_GetTicks();
		Uint32 elapsedTime = currentTime - startTimeFadeOut;

		const Uint32 fadeDuration = 1000;

		if (elapsedTime < fadeDuration) {
			float progress = static_cast<float>(elapsedTime) / fadeDuration;
			opacity = static_cast<Uint8>(255 * (1-progress));
		}
		else {
			opacity = 0;
			done = true;
		}
	}
}
