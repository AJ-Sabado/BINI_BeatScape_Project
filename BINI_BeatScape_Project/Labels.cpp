#include "Labels.h"

BINI::Labels::Labels(BINI::Renderer* renderer, BINI::Font* font, std::string textureText, SDL_Color textColor)
{
	lTexture = NULL;
	lWidth = 0;
	lHeight = 0;
	SDL_Surface* textSurface = TTF_RenderText_Solid(font->getFont(), textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		std::cout << "Unable to render text surface! SDL ttf Error: " << TTF_GetError() << "\n";
	}
	else
	{
		lTexture = SDL_CreateTextureFromSurface(renderer->getRenderer(), textSurface);
		if (lTexture == NULL)
		{
			std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << "\n";
		}
		else
		{
			lWidth = textSurface->w;
			lHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}
}

BINI::Labels::~Labels()
{
	if (lTexture != NULL)
	{
		SDL_DestroyTexture(lTexture);
		lTexture = NULL;
		lWidth = 0;
		lHeight = 0;
	}
}

void BINI::Labels::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture
	SDL_SetTextureColorMod(lTexture, red, green, blue);
}

void BINI::Labels::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(lTexture, blending);
}

void BINI::Labels::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(lTexture, alpha);
}

void BINI::Labels::render(BINI::Renderer* renderer, int x, int y, SDL_Rect* clip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, lWidth, lHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(renderer->getRenderer(), lTexture, clip, &renderQuad);
}

int BINI::Labels::getWidth()
{
	return lWidth;
}

int BINI::Labels::getHeight()
{
	return lHeight;
}