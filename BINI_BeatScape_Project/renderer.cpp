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
	//Cleanup
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