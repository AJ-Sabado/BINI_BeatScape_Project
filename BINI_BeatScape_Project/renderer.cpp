#include "Renderer.h"

BINI::Renderer::Renderer(BINI::Window window)
{
	bRenderer = NULL;

	if (window.getWindow() != NULL)
	{
		bRenderer = SDL_CreateRenderer(window.getWindow(), -1, SDL_RENDERER_ACCELERATED);
		if (bRenderer == NULL)
		{
			std::cout << "Unable to create renderer! SDL Error: " << SDL_GetError() << "\n";
		}
		else
		{
			SDL_SetRenderDrawColor(bRenderer, 255, 255, 255, 255);
		}
	}
}

BINI::Renderer::~Renderer()
{
	if (bRenderer != NULL)
	{
		SDL_DestroyRenderer(bRenderer);
		bRenderer = NULL;
	}
}

void BINI::Renderer::clearScreen()
{
	SDL_SetRenderDrawColor(bRenderer, 255, 255, 255, 255);
	SDL_RenderClear(bRenderer);
}


void BINI::Renderer::update()
{
	SDL_RenderPresent(bRenderer);
}


