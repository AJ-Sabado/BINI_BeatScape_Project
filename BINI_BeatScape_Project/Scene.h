#pragma once

#include "Renderer.h"

namespace BINI 
{
	class Scene
	{
	public:

		Scene();

		~Scene();

		bool isTransitioning();

		void willTransition();

		//Displays the scene
		virtual void display(BINI::Renderer* renderer) = 0;

	private:
		bool transitionState;
	};
}


