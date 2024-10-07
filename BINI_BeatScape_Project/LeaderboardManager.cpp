#include "LeaderboardManager.h"

namespace BINI
{
	LeaderboardManager::LeaderboardManager(std::string path)
	{
		std::ifstream myFile(path);

		if (!myFile.is_open())
		{
			std::ofstream newFile(path);
			newFile << "";

			if (newFile.is_open())
			{
				std::cout << "File created\n";
			}

			newFile.close();
			return;
		}

		std::string line;
		ScoreContainer* temp;

		while (getline(myFile, line))
		{
			std::string userInitials = line;
			getline(myFile, line);
			std::string userDifficulty = line;
			getline(myFile, line);
			int score = std::stoi(line);
			getline(myFile, line);
			int maxCombo = std::stoi(line);
			getline(myFile, line);
			float accuracy = std::stof(line);
			getline(myFile, line);
			if (line[0] == '#')
			{
				temp = new ScoreContainer(score, maxCombo, accuracy, userInitials, userDifficulty);
				if (head != NULL)
				{
					tail->next = temp;
					tail = tail->next;
				}
				else
				{
					head = temp;
					tail = head;
				}
			}
		}

		std::cout << "File loaded\n";
		myFile.close();
	}

	LeaderboardManager::~LeaderboardManager()
	{
		if (head == NULL)
		{
			return;
		}

		while (head != tail)
		{
			ScoreContainer* toDel = head;
			head = head->next;
			delete toDel;
		}

		if (tail != NULL)
		{
			delete tail;
		}

		head = NULL;
		tail = NULL;
	}

	void LeaderboardManager::addItem(ScoreContainer* newScore)
	{
		if (head == NULL)
		{
			head = newScore;
			tail = head;
			return;
		}

		//top insert
		if (newScore->score >= head->score)
		{
			newScore->next = head;
			head = newScore;
			return;
		}

		//middle insert
		ScoreContainer* prev = head;
		ScoreContainer* current = head->next;

		while (current->next != tail && current->score > newScore->score)
		{
			prev = current;
			current = current->next;
		}

		if (newScore->score >= current->score)
		{
			prev->next = newScore;
			newScore->next = current;
		}

		//bottom insert
		if (tail->score >= newScore->score)
		{
			tail->next = newScore;
			tail = tail->next;
		}

	}

	void LeaderboardManager::exportFile(std::string path)
	{
		displayList();
		std::ofstream newFile(path);

		ScoreContainer* current = head;

		while (current != NULL)
		{
			newFile << current->userInitials << "\n"
				<< current->userDifficulty << "\n"
				<< current->score << "\n"
				<< current->maxCombo << "\n"
				<< current->accuracy << "\n#\n";
			current = current->next;
		}

		newFile.close();

	}
	
	void LeaderboardManager::displayList()
	{
		ScoreContainer* current = head;

		while (current != NULL)
		{
			std::cout << current->score << "\n";
			current = current->next;
		}

	}
	
}

