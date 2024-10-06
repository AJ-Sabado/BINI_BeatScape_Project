#include "Renderer.h"

BINI::Renderer::Renderer(BINI::Window* window)
{

	maxWidth = window->getWindowWidth();

	maxHeight = window->getWindowHeight();

	bRenderer = SDL_CreateRenderer(window->getCurrentWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (bRenderer == NULL)
	{
		std::cout << "Unable to create SDL renderer! SDL Error: " << SDL_GetError() << "\n";
	}
	else
	{
		SDL_SetRenderDrawColor(bRenderer, 255, 255, 255, 255);
		std::cout << "SDL renderer created\n";
	}
}

BINI::Renderer::~Renderer()
{
	if (bRenderer != NULL)
	{
		SDL_DestroyRenderer(bRenderer);
		bRenderer = NULL;
		std::cout << "SDL renderer destroyed.\n";
	}
}

void BINI::Renderer::clearScreen()
{
	SDL_SetRenderDrawColor(bRenderer, 0, 0, 0, 255);
	SDL_RenderClear(bRenderer);
}

void BINI::Renderer::updateScreen()
{
	SDL_RenderPresent(bRenderer);
}

int BINI::Renderer::getMaxWidth()
{
	return maxWidth;
}

int BINI::Renderer::getMaxHeight()
{
	return maxHeight;
}

void BINI::Renderer::fadingOut(int duration)
{
    const int frameCount = 60;
    const int frameDuration = duration / frameCount;

    for (int i = 0; i <= frameCount; ++i)
    {
        Uint8 alpha = static_cast<Uint8>((1.0f - static_cast<float>(i) / frameCount) * 255);
        SDL_SetRenderDrawColor(bRenderer, 0, 0, 0, alpha);
        SDL_RenderClear(bRenderer);
        SDL_RenderFillRect(bRenderer, nullptr);
        updateScreen();
        SDL_Delay(frameDuration);
    }

    SDL_SetRenderDrawColor(bRenderer, 0, 0, 0, 255);
    SDL_RenderClear(bRenderer);
    updateScreen();
}
