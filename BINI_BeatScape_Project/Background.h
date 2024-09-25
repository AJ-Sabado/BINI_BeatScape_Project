#pragma once

#include "SDL.h"
#include "SDL_image.h"

namespace BINI
{
	class Background
	{
	public:

		Background();

		~Background();


	private:
		SDL_Texture* bTexture;
		int width;
		int height;
	};
}


