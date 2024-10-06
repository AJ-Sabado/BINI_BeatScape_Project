#pragma once

#include "SDL_mixer.h"
#include "string"
#include "iostream"
#include <chrono>
#include <thread>

namespace BINI
{
	//Contains SDL mixer Music
	class Music
	{
	public:
		//Music constructor
		Music(std::string path);

		//Music destructor
		~Music();

		//Plays music from the start; loops: 0 to play once, -1 to loop.
		void startMusic(int loops);

		//Stops music.
		void stopMusic();

		//Pauses music.
		void pauseMusic();

		//Resumes music.
		void resumeMusic();

		// Fades out music over a specified duration (in milliseconds).
		static void fadeOutMusic(int duration);

		//Returns true if music is playing.
		bool isPlaying();

		/*static void playBGMusic();
		static void endBGMusic();*/

	private:
		//Mixer hardware
		Mix_Music* bMusic;

		
	};
}



