#pragma once

#include "Renderer.h"

namespace BINI
{
	class Background
	{
	public:

		Background(BINI::Renderer* renderer, std::string path);

		~Background();

		void draw(BINI::Renderer* renderer);

	private:

		SDL_Texture* bTexture;
	};
}



