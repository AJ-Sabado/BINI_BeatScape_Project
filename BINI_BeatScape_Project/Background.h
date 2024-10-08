#pragma once

#include "Renderer.h"
#include "Texture.h"

namespace BINI
{
	//Contains background elements.
	class Background
	{
	public:

		//Background constructor.
		Background(BINI::Renderer* renderer, std::string path);

		//Background destructor.
		~Background();

		//Renders the background.
		void draw(BINI::Renderer* renderer);

	private:

		//Texture object
		BINI::Texture* bTexture;

		//Opacity
		Uint8 alpha;
	};
}



