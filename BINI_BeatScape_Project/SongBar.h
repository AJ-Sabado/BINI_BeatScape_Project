#pragma once

#include "Note.h"
#include "iostream"

namespace BINI
{
	//Structure SongBar. A list of this makes up a chart. Also contains the 4 notes objects.
	struct SongBar
	{
		//Constructor
		SongBar();

		//Destructor
		~SongBar();

		//Notes
		BINI::Note* d;
		BINI::Note* f;
		BINI::Note* j;
		BINI::Note* k;

		bool isAlive;

		float totalY;
	};
}


