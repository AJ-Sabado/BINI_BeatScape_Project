#pragma once

#include "SDL_ttf.h"
#include "string"

namespace BINI
{
	//Contains TTF renderer (font).
	class Font
	{
	public:
		//Font constructor.
		Font(std::string path, int ptSize);

		//Font deconstructor.
		~Font();

		//Returns hardware font for labels to use
		inline TTF_Font* getFont() { return bFont; }

	private:

		//Hardware font.
		TTF_Font* bFont;
	};
}



