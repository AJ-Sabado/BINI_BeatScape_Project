#pragma once

#include "Renderer.h"
#include "Events.h"

namespace BINI 
{
	//Scene abstract class
	class Scene
	{
	public:

		//Scene deconstructor.
		virtual ~Scene() {};

		//Displays the scene
		virtual void display(BINI::Renderer* renderer) = 0;

		//Should return false if your scene is done/ready to exit/transition.
		virtual bool isDone() = 0;

		virtual bool handleEvents(BINI::Events* events) = 0;
	};
}


