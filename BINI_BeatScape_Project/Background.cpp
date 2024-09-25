#include "Background.h"

BINI::Background::Background(BINI::Renderer* renderer, std::string path)
{
	bTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image " << path << "! SDl image Error: " << IMG_GetError() << "\n";
	}
	else
	{
		bTexture = SDL_CreateTextureFromSurface(renderer->getRenderer(), loadedSurface);
		if (bTexture == NULL)
		{
			std::cout << "Unable to create texture from image " << path << "! SDL Error: " << SDL_GetError() << "\n";
		}
		else
		{
			std::cout << "Background texture created.\n";
		}
	}
	SDL_FreeSurface(loadedSurface);
}

BINI::Background::~Background()
{
	if (bTexture != NULL)
	{
		SDL_DestroyTexture(bTexture);
		bTexture = NULL;
		std::cout << "Background destroyed.\n";
	}
}

void BINI::Background::draw(BINI::Renderer* renderer)
{
	SDL_RenderCopy(renderer->getRenderer(), bTexture, NULL, NULL);
}