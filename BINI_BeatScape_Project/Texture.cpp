#include "Texture.h"

BINI::Texture::Texture(BINI::Renderer* renderer, std::string path)
{
	bTexture = NULL;
	bWidth = 0;
	bHeight = 0;

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer->getRenderer(), loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			bWidth = loadedSurface->w * renderer->getMaxWidth() / 1920;
			bHeight = loadedSurface->h * renderer->getMaxHeight() / 1080;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	bTexture = newTexture;
}

BINI::Texture::~Texture()
{
	//Cleanup
	if (bTexture != NULL)
	{
		SDL_DestroyTexture(bTexture);
		bTexture = NULL;
		bWidth = 0;
		bHeight = 0;
		std::cout << "Texture destroyed.\n";
	}
}

void BINI::Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture
	SDL_SetTextureColorMod(bTexture, red, green, blue);
}

void BINI::Texture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(bTexture, blending);
}

void BINI::Texture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(bTexture, alpha);
}

void BINI::Texture::render(BINI::Renderer* renderer, int x, int y, SDL_Rect* clip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, bWidth, bHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(renderer->getRenderer(), bTexture, clip, &renderQuad);
}

int BINI::Texture::getWidth()
{
	return bWidth;
}

int BINI::Texture::getHeight()
{
	return bHeight;
}