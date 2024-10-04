#pragma once

#include "Scene.h"
#include "Renderer.h"
#include "Texture.h"
#include "Events.h"
#include "Font.h"
#include "Labels.h"

namespace BINI
{
	class CompanyLogo : public BINI::Scene
	{
	public:

		CompanyLogo(BINI::Renderer* renderer);

		~CompanyLogo() override;

		virtual void display(BINI::Renderer* renderer) override;

		virtual bool isDone() override;

		virtual bool handleEvents(BINI::Events* events) override;

		void fade_in();

		void fade_out();

	private:
		Texture* background;
		Texture* logo;
		Uint8 opacity = 0;

		Uint32 startTimeFadeIn;
		Uint32 startTimeFadeOut;

		//Fonts and Labels
		Font* steelar;
		Font* bebas;
		Labels* instruction;
		Labels* pressStart;

		int enter = 0;

		bool done;
	};
}


