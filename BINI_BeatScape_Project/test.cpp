///*
//This is currently a temporary solution for rendering while the renderering class is being developed.
//*/
//#include <SDL.h>
//#include <SDL_image.h>
//#include <iostream>
//#include <string>
//
//using std::string;
//using std::cout;
//
//const int SCREEN_WIDTH = 1280;
//const int SCREEN_HEIGHT = 720;
//
//SDL_Window* gameWindow = NULL;
//SDL_Surface* gameScreenSurface = NULL;
//SDL_Surface* gameBackgroundSurface = NULL;
//
//bool init();
//bool loadMedia();
//void close();
//SDL_Surface* loadSurface(string path);
//
//bool init()
//{
//	bool success = true;
//	if (SDL_Init(SDL_INIT_VIDEO) < 0)
//	{
//		cout << "SDL failed to initialize! SDL Error:\n" << SDL_GetError();
//		success = false;
//	}
//	else
//	{
//		gameWindow = SDL_CreateWindow("BINI BeatScape", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//		if (gameWindow == NULL)
//		{
//			cout << "Window could not be created! SDL Error:\n" << SDL_GetError();
//			success = false;
//		}
//		else
//		{
//			int imgFlags = IMG_INIT_PNG;
//			if (!(IMG_Init(imgFlags) & imgFlags))
//			{
//				cout << "SDL_image failed to initialize! SDL Error:\n" << IMG_GetError();
//				success = false;
//			}
//			else
//			{
//				gameScreenSurface = SDL_GetWindowSurface(gameWindow);
//			}
//		}
//	}
//
//	return success;
//}
//
//bool loadMedia()
//{
//	bool success = true;
//	gameBackgroundSurface = loadSurface("assets/textures/bg.png");
//	if (gameBackgroundSurface == NULL)
//	{
//		cout << "Failed to load background image!\n";
//		success = false;
//	}
//
//	return success;
//}
//
//SDL_Surface* loadSurface(string path)
//{
//	SDL_Surface* optimizedSurface = NULL;
//	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
//	if (loadedSurface == NULL)
//	{
//		cout << "Unable to load image! SDL_image Error:\n" << path.c_str() << IMG_GetError();
//	}
//	else
//	{
//		optimizedSurface = SDL_ConvertSurface(loadedSurface, gameScreenSurface->format, 0);
//		if (optimizedSurface == NULL)
//		{
//			cout << "Unable to optimize image! SDL_image Error:\n" << path.c_str() << SDL_GetError();
//		}
//		SDL_FreeSurface(loadedSurface);
//	}
//	return optimizedSurface;
//}
//
//void close()
//{
//	SDL_FreeSurface(gameBackgroundSurface);
//	gameBackgroundSurface = NULL;
//	SDL_DestroyWindow(gameWindow);
//	gameWindow = NULL;
//	IMG_Quit();
//	SDL_Quit();
//}
//
//int main(int argc, char* args[])
//{
//	if (!init())
//	{
//		cout << "Failed to initialize!\n";
//	}
//	else
//	{
//		if (!loadMedia())
//		{
//			cout << "Failed to load media!\n";
//		}
//		else
//		{
//			bool quit = false;
//			SDL_Event e;
//			while (!quit)
//			{
//				while (SDL_PollEvent(&e) != 0)
//				{
//					if (e.type == SDL_QUIT)
//					{
//						quit = true;
//					}
//
//					SDL_Rect stretchBGRect;
//					stretchBGRect.x = 0;
//					stretchBGRect.y = 0;
//					stretchBGRect.w = SCREEN_WIDTH;
//					stretchBGRect.h = SCREEN_HEIGHT;
//
//					SDL_BlitScaled(gameBackgroundSurface, NULL, gameScreenSurface, NULL);
//
//					SDL_UpdateWindowSurface(gameWindow);
//
//
//				}
//			}
//		}
//	}
//	close();
//	return 0;
//}