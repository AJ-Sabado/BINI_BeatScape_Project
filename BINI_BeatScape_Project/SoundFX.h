#pragma once

#include "SDL_mixer.h"
#include "string"
#include "iostream"

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

	private:

		Mix_Chunk* bSFX;
	};
}


