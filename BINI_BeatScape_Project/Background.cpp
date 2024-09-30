#include "Background.h"

BINI::Background::Background(BINI::Renderer* renderer, std::string path)
{
	alpha = 0;
	bTexture = new BINI::Texture(renderer, path);
	bTexture->setBlendMode(SDL_BLENDMODE_BLEND);
}

BINI::Background::~Background()
{
	if (bTexture != NULL)
	{
		delete bTexture;
		bTexture = NULL;
	}
}

void BINI::Background::draw(BINI::Renderer* renderer)
{
	//fades in on draw
	if (alpha + 5 >  255)
	{
		
		alpha = 255;
	}
	else
	{
		alpha += 5;
	}

	bTexture->setAlpha(alpha);
	bTexture->render(renderer, 0, 0);
}