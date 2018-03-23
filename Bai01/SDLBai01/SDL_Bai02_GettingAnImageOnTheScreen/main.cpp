#include <iostream>
#include <SDL.h>
// Load 1 file media vào window

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
// Loads Media
bool loadMedia();
// frees media and shuts down SDL
void close();

SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;
// Tải và show hình ảnh lên màn hình
SDL_Surface *gHelloWorld = NULL;

int main(int argc, char* args[])
{
	if (!init())
	{
		std::cout << "Failed to initialize!\n";
	}
	else
	{
		// Load media
		if (!loadMedia())
		{
			std::cout << "Failed to load media!\n";
		}
		else
		{
			// đổ surface gHelloWorld vào surface screenWindow sử dụng SDL_BlitSurface
			// Apply the image
			SDL_BlitSurface(gHelloWorld, NULL, screenSurface, NULL);
			SDL_UpdateWindowSurface(window);
			SDL_Delay(5000);
		}
	}
	close();
	return 0;
}

bool init()
{
	// Initialization flag
	bool success = true;
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error :" << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		window = SDL_CreateWindow("Getting An Image On The Screen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			std::cout << "Window could not be created! SDL_Error :" << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
		}
	}
	return success;
}
void close()
{
	// Deallocate surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;
	// Destroy window
	SDL_DestroyWindow(window);
	window = NULL;
	// Quit SDL subsystems
	SDL_Quit();
}
bool loadMedia()
{
	// Loading success flag
	bool success = true;
	// Load image01 image
	gHelloWorld = SDL_LoadBMP("Image/image01.bmp");
	if (gHelloWorld == NULL)
	{
		std::cout << "Unable to load image " << "Image/image01.bmp," << SDL_GetError()<< std::endl;
		success = false;
	}
	return success;
}