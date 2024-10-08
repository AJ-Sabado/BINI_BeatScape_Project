#include "Music.h"

BINI::Music::Music(std::string path)
{
	bMusic = Mix_LoadMUS(path.c_str());
	if (bMusic == NULL)
	{
		std::cout << "Unable to load music from file " << path << "! SDL mixer Error: " << Mix_GetError() << "\n";
	}
}

BINI::Music::~Music()
{
	//Cleanup
	if (bMusic != NULL)
    {
        Mix_HaltMusic();  
        Mix_FreeMusic(bMusic);
        bMusic = NULL;
    }
}

void BINI::Music::startMusic(int loops)
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(bMusic, loops);
	}
}

void BINI::Music::stopMusic()
{
	if (Mix_PlayingMusic() == 1)
	{
		Mix_HaltMusic();
	}
}

void BINI::Music::resumeMusic()
{
	if (Mix_PausedMusic() == 1)
	{
		Mix_ResumeMusic();
	}
}

void BINI::Music::pauseMusic()
{
	if (Mix_PausedMusic() == 0)
	{
		Mix_PauseMusic();
	}
}

bool BINI::Music::isPlaying()
{
	return Mix_PlayingMusic();
}


void BINI::Music::fadeOutMusic(int duration)
{
	Mix_FadeOutMusic(duration);
}

void BINI::Music::playBGMusic() {
	static Music bgMusic("assets/music/Menu/Salamin_Rock.mp3");
	bgMusic.startMusic(-1);
}