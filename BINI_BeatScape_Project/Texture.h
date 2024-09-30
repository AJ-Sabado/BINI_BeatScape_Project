#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Renderer.h"
#include "string"

namespace BINI
{
	//Contains SDL texture
	class Texture
	{
	public:
		//Texture constructor
		Texture(BINI::Renderer* renderer, std::string path);

		//Texture deconstructor
		~Texture();

		//Set color modulation
		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		//Set blending
		void setBlendMode(SDL_BlendMode blending);

		//Set alpha modulation
		void setAlpha(Uint8 alpha);
		
		//Renders texture at given point
		void render(BINI::Renderer* renderer, int x, int y, SDL_Rect* clip = NULL);

		//Gets image width
		int getWidth();

		//Gets image height
		int getHeight();

	private:
		//Actual hardware texture
		SDL_Texture* bTexture;

		int bWidth;
		int bHeight;
	};
}


