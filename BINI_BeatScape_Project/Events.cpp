#include "Events.h"

BINI::Events::Events()
{
	//Init player data
	currentState = BINI_LOGO;
	clearUserData();
}

BINI::Events::~Events()
{
	//Perform cleanup
	currentState = 0;
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

void BINI::Events::setUserData(int score, int maxcombo)
{
	userScore = score;
	userMaxCombo = maxcombo;
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


//Removes previously stored user data
void BINI::Events::clearUserData()
{
	userMaxCombo = 0;
	userScore = 0;
}

