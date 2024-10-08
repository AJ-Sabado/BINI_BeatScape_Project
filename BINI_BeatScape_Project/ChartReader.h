#pragma once

#include "fstream"
#include "SongBar.h"
#include "queue"
#include "string"

namespace BINI
{
	//Loads chart files of type .bchart.
	class ChartReader
	{
	public:
		//ChartReader constructor.
		ChartReader();

		//Returns the parsed chart of specified chart file.
		std::queue<BINI::SongBar*> loadSong(std::string path);

	private:

		//Stores lines for processing.
		std::string line;
		int data;
	};

}



