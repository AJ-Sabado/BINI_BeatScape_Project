#pragma once

#include "Scene.h"
#include "Renderer.h"
#include "Texture.h"

namespace BINI
{
	class CompanyLogo : public BINI::Scene
	{
	public:

		CompanyLogo();

		~CompanyLogo();

		virtual void display(BINI::Renderer* renderer);

	private:

		Texture* background;
	};
}


