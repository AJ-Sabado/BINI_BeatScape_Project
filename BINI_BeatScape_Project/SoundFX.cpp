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

void BINI::SoundFX::playSlideSFX() {
	SoundFX* slide = new SoundFX("assets/sfx/menuSlideSFX.wav");
	slide->playSFX();
}

void BINI::SoundFX::playEnterSFX() {
	SoundFX* enter = new SoundFX("assets/sfx/Enter_Pressed_SFX.wav");
	enter->playSFX();
}
