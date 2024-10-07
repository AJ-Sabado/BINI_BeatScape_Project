#pragma once

#include "string"

namespace BINI
{
	struct ScoreContainer
	{
		int score = 0;
		int maxCombo = 0;
		float accuracy = 0.f;
		std::string userInitials = "";
		std::string userDifficulty = "";
		BINI::ScoreContainer* next = NULL;

		ScoreContainer(int newScore, int newMaxCombo, float newAccuracy, std::string newInitials, std::string newDiff);

	};
}



