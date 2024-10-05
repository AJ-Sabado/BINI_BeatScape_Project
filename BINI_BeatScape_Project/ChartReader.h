#pragma once

#include "fstream"
#include "SongBar.h"
#include "queue"
#include "string"

namespace BINI
{
	class ChartReader
	{
	public:

		ChartReader();

		std::queue<BINI::SongBar*> loadSong(std::string path);

	private:

		std::string line;
		int data;
	};

}



