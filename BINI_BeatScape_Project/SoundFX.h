#pragma once

#include "SDL_mixer.h"
#include "string"
#include "iostream"
#include "SDL.h"

namespace BINI
{
	//Contains sfx *must be a .wav file!
	class SoundFX
	{
	public:
		//SoundFX constructor.
		SoundFX(std::string path);
		
		//SoundFX destructor.
		~SoundFX();

		//Plays stored SFX
		void playSFX();

		//Plays slide sfx in menus
		static void playSlideSFX();

		//Plays select sfx in menus
		static void playEnterSFX();

		//Plays when player fails game
		static void playGOLose();

		//Plays when player wins game
		static void playGOSuccess();

	private:
		//SDL mixer chunk which is the actual sound effect.
		Mix_Chunk* bSFX;
	};


}


