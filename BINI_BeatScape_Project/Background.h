#pragma once

#include "Renderer.h"

namespace BINI
{
	//Contains background elements.
	class Background
	{
	public:

		//Background constructor.
		Background(BINI::Renderer* renderer, std::string path);

		//Background deconstructor.
		~Background();

		//Renders the background.
		void draw(BINI::Renderer* renderer);

	private:

		SDL_Texture* bTexture;
	};
}



