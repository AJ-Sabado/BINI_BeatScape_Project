#include "Font.h"

BINI::Font::Font(std::string path, int ptSize)
{
	bFont = TTF_OpenFont(path.c_str(), ptSize);
}

BINI::Font::~Font()
{
	//Cleanup
	if (bFont != NULL)
	{
		TTF_CloseFont(bFont);
		bFont = NULL;
	}
}