#pragma once

#include "string"
#include "ScoreContainer.h"
#include "fstream"
#include "iostream"

using BINI::ScoreContainer;

namespace BINI
{
	//Imports and exports leaderboard file with .bBoard type
	class LeaderboardManager
	{
	public:
		//Constructor
		LeaderboardManager(std::string path);

		//Destructor
		~LeaderboardManager();

		//Adds entry to current score list
		void addItem(ScoreContainer* newScore);

		//Exports list to a .bBoard file
		void exportFile(std::string path);

		//Returns current score list
		ScoreContainer* getScoreList() { return head; };

	private:
		//Score Container list
		ScoreContainer* head = NULL;
		ScoreContainer* tail = head;

		//Displays list on console	*debug
		void displayList();

	};
}



