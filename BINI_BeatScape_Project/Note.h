#pragma once

enum NOTE_POSITION
{
	NOTE_NAN,
	NOTE_FIRST,
	NOTE_SECOND,
	NOTE_THIRD,
	NOTE_FOURTH
};

namespace BINI
{
	//Structure Note. A queue of notes make up a chart.
	struct Note
	{
		//Note constructor
		Note(int release);

		//Y Position of a note.
		float noteYPos;

		//Release duration of a note
		int releaseDuration;

		bool isAlive;

		void kill();

	};
}



