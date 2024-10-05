#include "ChartReader.h"

BINI::ChartReader::ChartReader()
{
	data = 0;
}

std::queue<BINI::SongBar*> BINI::ChartReader::loadSong(std::string path)
{
	std::ifstream inputFile(path);

	std::queue<BINI::SongBar*> song;

	if (!inputFile.is_open())
	{
		std::cout << "File not found.\n";
		return song;
	}

	while (getline(inputFile, line))
	{
		BINI::SongBar* newBar = new SongBar;

		data = std::stoi(line);
		if (data == 1)
		{
			newBar->d = new BINI::Note(1);
		}
		getline(inputFile, line);
		data = std::stoi(line);
		if (data == 1)
		{
			newBar->f = new BINI::Note(1);
		}
		getline(inputFile, line);
		data = std::stoi(line);
		if (data == 1)
		{
			newBar->j = new BINI::Note(1);
		}
		getline(inputFile, line);
		data = std::stoi(line);
		if (data == 1)
		{
			newBar->k = new BINI::Note(1);
		}
		getline(inputFile, line);
		if (line[0] == '#')
		{
			song.push(newBar);
			continue;
		}
	}

	inputFile.close();

	return song;
}