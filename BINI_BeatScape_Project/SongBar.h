#pragma once

#include "Note.h"
#include "iostream"

namespace BINI
{
	struct SongBar
	{
		SongBar();

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


