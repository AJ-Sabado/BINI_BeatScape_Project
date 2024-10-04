#include "Events.h"

BINI::Events::Events()
{
	currentState = BINI_START;
	currentState = BINI_LOGO;
	currentState = BINI_SONG_EASY;
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

