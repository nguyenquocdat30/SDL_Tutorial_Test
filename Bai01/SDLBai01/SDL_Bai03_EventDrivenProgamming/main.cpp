#include <iostream>
#include <SDL.h>
// Xử lí sự kiện nút X cho window
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenWindow = NULL;
SDL_Surface *gLoadImage = NULL;


int main(int argc, char *args[])
{
	// main loop flag
	bool quit = false;
	// event handler
	SDL_Event e;

	if (!init())
	{
		std::cout << "Failed to initlize! \n";
	}
	else
	{
		if (!loadMedia())
		{
			std::cout << "Failed to load image ! \n";
		}
		else
		{
			// loop game
			while (!quit)
			{
				// Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					// User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
				SDL_BlitSurface(gLoadImage, NULL, gScreenWindow, NULL);
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}
	close();
	return 0;
}
bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error :" << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("Event Driven Programming", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			std::cout << "Window could not be created! SDL_Error : " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			gScreenWindow = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}
void close()
{
	SDL_FreeSurface(gLoadImage);
	gLoadImage = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gScreenWindow = NULL;
	SDL_Quit();
}
bool loadMedia()
{
	bool success = true;
	gLoadImage = SDL_LoadBMP("Image/img01.bmp");
	if (gLoadImage == NULL)
	{
		std::cout << "Unable to load image" << "Image/img01.bmp " << SDL_GetError() << std::endl;
		success = false;
	}
	return success;
}