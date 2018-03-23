#include "LTexture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
// The Window
SDL_Window *gWindow = NULL;
// The window renderer
SDL_Renderer *gRenderer = NULL;
// Scene texture
LTexture gFooTexture;
LTexture gBackgroundTexture;
bool init();
bool loadMedia();
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
			std::cout << "Failed to load Media \n";
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
				// to do
				// clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				// render background texture to screen
				gBackgroundTexture.render(0, 0, gRenderer);
				// render foo texture to screen
				gFooTexture.render(240, 190, gRenderer);
				SDL_RenderPresent(gRenderer);
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
		std::cout << "SDL could not initialize ! SDL_Error ! " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning : Linear texture filtering not enable\n";
		}
		gWindow = SDL_CreateWindow("Color Key", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			std::cout << "Window could not be created ! SDL_Error " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				std::cout << "Renderer could not be created ! SDL_Error " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags)&imgFlags))
				{
					std::cout << "SDL_image could not initialize ! SDL_Image " << IMG_GetError() << std::endl;
					success = false;
				}
			}
		}
	}
	return success;
}
bool loadMedia()
{
	bool success = true;
	if (!gFooTexture.loadFromFile("foo.png",gRenderer))
	{
		std::cout << "Failed to load Foo Texture image\n";
		success = false;
	}
	if (!gBackgroundTexture.loadFromFile("background.png",gRenderer))
	{
		std::cout << "Failed to load Background Texture image \n";
		success = false;
	}
	return success;
}
void close()
{
	// free loaded images
	gFooTexture.free();
	gBackgroundTexture.free();
	// Destroy window
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	gWindow = NULL;
	gRenderer = NULL;
	// Quit SDL subsystems

	IMG_Quit();
	SDL_Quit();
}