#pragma once

#include "Scene.h"
#include "Renderer.h"
#include "Texture.h"

namespace BINI
{
	class CompanyLogo : public BINI::Scene
	{
	public:

		CompanyLogo(BINI::Renderer* renderer);

		~CompanyLogo();

		virtual void display(BINI::Renderer* renderer);

		virtual bool isDone();

	private:

		Texture* background;

		Uint8 opacity;

		Uint32 currentTime;

		bool done;
	};
}


