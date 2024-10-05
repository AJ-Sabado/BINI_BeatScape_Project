#include "SongBar.h"

namespace BINI
{
	SongBar::SongBar()
	{
		d = NULL;
		f = NULL;
		j = NULL;
		k = NULL;

		totalY = 0;
	}

	SongBar::~SongBar()
	{
		delete d;
		d = nullptr;
		delete f;
		f = nullptr;
		delete j;
		j = nullptr;
		delete k;
		k = nullptr;

		//std::cout << "Bar deleted.\n";
	}
}