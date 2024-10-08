#include "Events.h"

BINI::Events::Events()
{
	//Init player data
	currentState = BINI_LOGO;
	clearUserData();
	
	leaderboardmanager = new BINI::LeaderboardManager(leadboardPath.c_str());
}

BINI::Events::~Events()
{
	//Perform cleanup
	currentState = 0;
	
	if (leaderboardmanager != NULL)
	{
		delete leaderboardmanager;
		leaderboardmanager = NULL;
	}
}

int BINI::Events::pollEvents()
{
	return SDL_PollEvent(&e);
}

Uint32 BINI::Events::type()
{
	return e.type;
}

Uint32 BINI::Events::getKey()
{
	return e.key.keysym.sym;
}

void BINI::Events::setState(int state)
{
	currentState = state;
}

bool BINI::Events::repeat()
{
	return e.key.repeat;
}

int BINI::Events::getCurrentState()
{
	return currentState;
}

void BINI::Events::setUserData(int score, int maxcombo, std::string difficulty, float accuracy)
{
	userScore = score;
	userMaxCombo = maxcombo;
	userDifficulty = difficulty;
	userAccuracy = accuracy;
}

void BINI::Events::setUserInitials(std::string initials)
{
	userInitials = initials;
}

//Returns user score
int BINI::Events::getUserScore()
{
	return userScore;
}

//Returns user max combo
int BINI::Events::getUserMaxCombo()
{
	return userMaxCombo;
}

//Returns user accuray
float BINI::Events::getUserAccuracy()
{
	return userAccuracy;
}

std::string BINI::Events::getUserInitials()
{
	return userInitials;
}

std::string BINI::Events::getUserDifficulty()
{
	return userDifficulty;
}

//Removes previously stored user data
void BINI::Events::clearUserData()
{
	userInitials = "";
	userDifficulty = "";
	userScore = 0;
	userMaxCombo = 0;
	userAccuracy = 0.f;
}

void BINI::Events::exportData()
{
	//Performs leaderboard file export through leaderboard manager
	BINI::ScoreContainer* temp = new BINI::ScoreContainer(userScore, userMaxCombo, userAccuracy, userInitials, userDifficulty);
	leaderboardmanager->addItem(temp);
	leaderboardmanager->exportFile(leadboardPath);
	clearUserData();
}

BINI::ScoreContainer* BINI::Events::getScoreList()
{
	return leaderboardmanager->getScoreList();
}
