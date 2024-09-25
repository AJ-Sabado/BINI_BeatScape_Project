#include "Renderer.h"

BINI::Renderer::Renderer(BINI::Window* window)
{
	bRenderer = SDL_CreateRenderer(window->getCurrentWindow(), -1, SDL_RENDERER_ACCELERATED);
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
	SDL_SetRenderDrawColor(bRenderer, 255, 255, 255, 255);
	SDL_RenderClear(bRenderer);
}

void BINI::Renderer::updateScreen()
{
	SDL_RenderPresent(bRenderer);
}