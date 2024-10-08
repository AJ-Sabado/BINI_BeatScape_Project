#pragma once

#include "Scene.h"
#include "Renderer.h"
#include "Texture.h"
#include "Events.h"
#include "Font.h"
#include "Labels.h"

namespace BINI
{
	//Company Logo intro Scene
	class CompanyLogo : public BINI::Scene
	{
	public:
		//Constructor
		CompanyLogo(BINI::Renderer* renderer);

		//Destructor
		~CompanyLogo() override;

		//Displays the scene
		virtual void display(BINI::Renderer* renderer) override;

		//Returns true if scene is finished
		virtual bool isDone() override;

		//Handles key events for company logo scene
		virtual bool handleEvents(BINI::Events* events) override;

		//Fades scene in
		void fade_in();
		
		//Fades scene out
		void fade_out();

	private:
		//Textures
		Texture* background;
		Texture* logo;

		//Opacity value
		Uint8 opacity = 0;

		//Stores time values for fade in and fade out
		Uint32 startTimeFadeIn;
		Uint32 startTimeFadeOut;

		//Fonts and Labels
		Font* steelar;
		Font* bebas;
		Labels* instruction;
		Labels* pressStart;

		//State of which enter key is pressed
		int enter = 0;

		//If scene is ready to transition: true.
		bool done;
	};
}


