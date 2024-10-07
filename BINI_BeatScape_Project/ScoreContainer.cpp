#include "ScoreContainer.h"

BINI::ScoreContainer::ScoreContainer(int newScore, int newMaxCombo, float newAccuracy, std::string newInitials, std::string newDiff)
{
	score = newScore;
	maxCombo = newMaxCombo;
	accuracy = newAccuracy;
	userInitials = newInitials;
	userDifficulty = newDiff;
}
