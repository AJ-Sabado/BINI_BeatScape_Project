#pragma once

#include "SDl.h"

namespace BINI
{
	//Performs timing functions. Operates through SDL time calculation system.
	class Timer
	{
	public:
		//Constructor
		Timer();

		//Destructor
		~Timer();

		//Starts timer from the begininning.
		void start();

		//Stops timer
		void stop();

		//Pauses timer.
		void pause();

		//Resumes timer.
		void unpause();

		//Restarts timer.
		void restart();

		//Gets the timer's time
		Uint32 getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

	private:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
	};
}



