#include "ChartReader.h"

BINI::ChartReader::ChartReader()
{
	data = 0;
}

std::queue<BINI::SongBar*> BINI::ChartReader::loadSong(std::string path)
{
	std::ifstream inputFile(path);

	std::queue<BINI::SongBar*> song;

	//ends function if file is not found
	if (!inputFile.is_open())
	{
		std::cout << "File not found.\n";
		return song;
	}

	//chart file parser
	while (getline(inputFile, line))
	{
		int blankCheck = 0;
		BINI::SongBar* newBar = new BINI::SongBar;

		data = std::stoi(line);
		blankCheck += data;
		if (data == 1)
		{
			newBar->d = new BINI::Note(1);
		}
		getline(inputFile, line);
		data = std::stoi(line);
		blankCheck += data;
		if (data == 1)
		{
			newBar->f = new BINI::Note(1);
		}
		getline(inputFile, line);
		data = std::stoi(line);
		blankCheck += data;
		if (data == 1)
		{
			newBar->j = new BINI::Note(1);
		}
		getline(inputFile, line);
		data = std::stoi(line);
		blankCheck += data;
		if (data == 1)
		{
			newBar->k = new BINI::Note(1);
		}
		getline(inputFile, line);
		if (line[0] == '#')
		{
			if (blankCheck > 0)
				song.push(newBar);
			else
			{
				delete newBar;
				newBar = NULL;
				song.push(newBar);
			}
			continue;
		}
	}

	inputFile.close();

	return song;
}