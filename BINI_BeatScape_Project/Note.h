#pragma once

enum NOTE_POSITION 
{
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
		Note();

		//Note destructor
		~Note();

		//Sends note down
		void fallDown(float timeStep);

		//X Position of a note. 0 = first position, 1 = second, 2 = third, 3 = fourth.
		int noteXPos;

		//Y Position of a note.
		float noteYPos;

		//Down press window of a note
		int downWindow;

		//Release duration of a note
		int release;

	};
}



