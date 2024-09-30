#pragma once

#include "SDL.h"
#include "SDL_image.h"

namespace BINI
{
	class GameObject
	{
	public:

		GameObject();

		~GameObject();

	private:

		SDL_Texture* oTexture;
	};
}


