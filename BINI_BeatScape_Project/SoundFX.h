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

		static void playSlideSFX();
		static void playEnterSFX();
		static void playGOLose();
		static void playGOSuccess();

	private:

		Mix_Chunk* bSFX;
	};


}


