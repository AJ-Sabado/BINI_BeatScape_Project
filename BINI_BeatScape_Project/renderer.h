#pragma once
class Renderer
{
private:
	SDL_Renderer* gRenderer = NULL;
public:
	bool init();
};
