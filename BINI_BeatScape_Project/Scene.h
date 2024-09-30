#pragma once

#include "Renderer.h"

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

		//Returns true once scene is ready to exit
		//virtual bool exitScene(BINI::Renderer* renderer) = 0;
	};
}


