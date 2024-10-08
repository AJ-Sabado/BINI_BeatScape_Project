#include "SongBar.h"

namespace BINI
{
	SongBar::SongBar()
	{
		d = NULL;
		f = NULL;
		j = NULL;
		k = NULL;

		isAlive = true;

		totalY = 0;
	}

	SongBar::~SongBar()
	{
		//Cleanup
		if (d != NULL)
		{
			delete d;
			d = nullptr;
		}
		if (f != NULL)
		{
			delete f;
			f = nullptr;
		}
		if (j != NULL)
		{
			delete j;
			j = nullptr;
		}
		if (k != NULL)
		{
			delete k;
			k = nullptr;
		}
	}
}