#include "SoundFX.h"

BINI::SoundFX::SoundFX(std::string path)
{
	Mix_Volume(-1, MIX_MAX_VOLUME);
	bSFX = Mix_LoadWAV(path.c_str());
	if (bSFX == NULL)
	{
		std::cout << "Unable to load sfx " << path << "! SDL mixer Error: " << Mix_GetError() << "\n";
	}
}

BINI::SoundFX::~SoundFX()
{
	//cleanup
	if (bSFX != NULL)
	{
		Mix_FreeChunk(bSFX);
		bSFX = NULL;
	}
}

void BINI::SoundFX::playSFX()
{
	Mix_PlayChannel(-1, bSFX, 0);
}

void BINI::SoundFX::playSlideSFX()
{
	static SoundFX slide("assets/sfx/menuSlideSFX.wav");
	slide.playSFX();
}

void BINI::SoundFX::playEnterSFX()
{
	static SoundFX enter("assets/sfx/Enter_Pressed_SFX.wav"); 
	enter.playSFX();
}

void BINI::SoundFX::playGOLose() {
	static SoundFX lose("assets/sfx/Gave_Over_Failed.wav");
	lose.playSFX();
}

void BINI::SoundFX::playGOSuccess() {
	static SoundFX lose("assets/sfx/Game_over_completed.wav");
	lose.playSFX();
}
