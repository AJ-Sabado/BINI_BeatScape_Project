#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Renderer.h"
#include "Texture.h"
#include "string"

namespace BINI
{
	class GameObject
	{
	public:

		GameObject(BINI::Renderer* renderer, std::string path);

		~GameObject();

		void draw(BINI::Renderer* renderer, int x, int y);

	private:

		BINI::Texture* gTexture;
	};
}


