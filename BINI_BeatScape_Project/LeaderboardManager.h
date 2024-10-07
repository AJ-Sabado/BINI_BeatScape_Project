#pragma once

#include "string"
#include "ScoreContainer.h"
#include "fstream"
#include "iostream"

using BINI::ScoreContainer;

namespace BINI
{
	class LeaderboardManager
	{
	public:

		LeaderboardManager(std::string path);

		~LeaderboardManager();

		void addItem(ScoreContainer* newScore);

		void exportFile(std::string path);

		ScoreContainer* getScoreList() { return head; };

	private:

		ScoreContainer* head = NULL;
		ScoreContainer* tail = head;

		void displayList();

	};
}



