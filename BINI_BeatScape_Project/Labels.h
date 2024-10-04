#pragma once

#include "Renderer.h"
#include "Font.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

namespace BINI
{
	//Contains renderable texts
	class Labels
	{
	public:

		//Labels constructor.
		Labels(BINI::Renderer* renderer, BINI::Font* font, std::string textureText, SDL_Color textColor);

		//Labels deconstructor.
		~Labels();

		//Sets/Changes the text inside label.
		void setText(BINI::Renderer* renderer, BINI::Font* font, std::string textureText, SDL_Color textColor);
		
		//Set color modulation
		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		//Set blending
		void setBlendMode(SDL_BlendMode blending);

		//Set alpha modulation
		void setAlpha(Uint8 alpha);

		//Renders text at given point
		void render(BINI::Renderer* renderer, int x, int y, SDL_Rect* clip = NULL);

		//Gets label width
		int getWidth();

		//Gets label height
		int getHeight();

	private:

		//SDL texture of the label.
		SDL_Texture* lTexture;

		//Label width.
		int lWidth;

		//Label height.
		int lHeight;
	};
}



