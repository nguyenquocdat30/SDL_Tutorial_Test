#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenWindow = NULL;
// surface load png
SDL_Surface *gPNGSurface = NULL;

bool init();
bool loadMedia();
SDL_Surface *loadSurface(std::string path);
void close();

int main(int argc, char *args[])
{
	if (!init())
	{
		std::cout << "Failed to initialize!\n";
	}
	else
	{
		if (!loadMedia())
		{
			std::cout << "Failed to load Media!\n";
		}
		else
		{
			bool quit = false;
			SDL_Event e;
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
				//to do
				SDL_BlitSurface(gPNGSurface, NULL, gScreenWindow, NULL);
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}
	close();
	return 0;
}

//=====================================================================================================================
bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("Load PNG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags)&imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
			else
			{
				gScreenWindow = SDL_GetWindowSurface(gWindow);
			}
		}
	}
	return success;
}
SDL_Surface *loadSurface(std::string path)
{
	SDL_Surface *optimizeSurface = NULL;
	SDL_Surface *loadedSurface = NULL;
	loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image" << path.c_str() << " IMG Error" << IMG_GetError()<<std::endl;
	}
	else
	{
		optimizeSurface = SDL_ConvertSurface(loadedSurface, gScreenWindow->format, NULL);
		if (optimizeSurface == NULL)
		{
			std::cout << "Unable to optimize image " << path.c_str() << " SDL Error : " << SDL_GetError() << std::endl;
		}
		SDL_FreeSurface(loadedSurface);
		loadedSurface = NULL;
	}
	return optimizeSurface;
}
bool loadMedia()
{
	bool success = true;
	gPNGSurface = loadSurface("loaded.png");
	if (gPNGSurface == NULL)
	{
		std::cout << "Failed to load PNG image!\n";
		success = false;
	}
	return success;
}
void close()
{
	SDL_FreeSurface(gPNGSurface);
	gPNGSurface = NULL;

	//Destroy Window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gScreenWindow = NULL;
	//Quit IMG
	IMG_Quit();
	// Quit SDL
	SDL_Quit();
}