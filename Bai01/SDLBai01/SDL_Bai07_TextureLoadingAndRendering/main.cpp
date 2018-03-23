#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *gWindow = NULL;
// Loads individual image as texture
SDL_Texture *loadTexture(std::string path, SDL_Renderer *&gRenderer);
// The window renderer

// Current displayed texture
SDL_Texture *gTexture = NULL;

bool init(SDL_Renderer *&gRenderer);
bool loadMedia(SDL_Renderer *&gRenderer);
void close(SDL_Renderer *&gRenderer);

int main(int argc, char *args[])
{
	SDL_Renderer *gRenderer = NULL;
	if (!init(gRenderer))
	{
		std::cout << "Failed to initialize !\n";
	}
	else
	{
		if (!loadMedia(gRenderer))
		{
			std::cout << "Failed to load Media ! \n";
		}
		else
		{
			// loop game flags
			bool quit = false;
			// Event Handler 
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
				// Bai 07
				// clear screen
				//SDL_RenderClear(gRenderer);

				//// Render texture to screen
				//SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
				////Update Screen
				//SDL_RenderPresent(gRenderer);
				//======================================================================================================
				// bai 08
				// Clear screen 
				//SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				//SDL_RenderClear(gRenderer);

				//// Render red filled quad
				//SDL_Rect fillRect = { SCREEN_WIDTH / 4 , SCREEN_HEIGHT / 4,SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };
				//SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
				//SDL_RenderFillRect(gRenderer, &fillRect);
				//// render blue outline quad 
				//SDL_Rect outLineRect = { SCREEN_WIDTH / 5 , SCREEN_HEIGHT / 5 , SCREEN_WIDTH/5 *3 ,SCREEN_HEIGHT / 5 * 3 };
				//SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
				//SDL_RenderDrawRect(gRenderer, &outLineRect);
				//// Draw black vertical line
				//SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				//SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);
				//// Draw black horizontal line
				//SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				//SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2);
				////==================
				//SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				//for (int i = 0; i < SCREEN_HEIGHT; i= i+4)
				//{
				//	SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH/6 *2, i);
				//	SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 6 * 4, i);
				//}
				//SDL_RenderPresent(gRenderer);
				//================================================================================
				// Bai 09 View port
				// clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				// top left corner viewport
				SDL_Rect topLeftViewPort;
				topLeftViewPort.x = 0;
				topLeftViewPort.y = 0;
				topLeftViewPort.w = SCREEN_WIDTH / 2;
				topLeftViewPort.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport(gRenderer, &topLeftViewPort);
				// render texture to screen
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

				// top right corner viewport
				SDL_Rect topRightViewPort;
				topRightViewPort.x = SCREEN_WIDTH / 2;
				topRightViewPort.y = 0;
				topRightViewPort.w = SCREEN_WIDTH / 2;
				topRightViewPort.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport(gRenderer, &topRightViewPort);
				// render texture to screen
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

				// bottom corner viewport
				SDL_Rect bottomViewPort;
				bottomViewPort.x = 0;
				bottomViewPort.y = SCREEN_HEIGHT / 2;
				bottomViewPort.w = SCREEN_WIDTH;
				bottomViewPort.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport(gRenderer, &bottomViewPort);
				// render texture to screen
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

				SDL_RenderPresent(gRenderer);
				
			}
		}
	}
	close(gRenderer);
	system("pause");
	return 0;
}
bool init(SDL_Renderer *&gRenderer)
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize . SDL Error ! " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("Texture Loading and Rendering", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			std::cout << "Window could not be created ! SDL Error : " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			// create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				std::cout << "Renderer could not be created . SDL Error " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) &imgFlags))
				{
					std::cout << "SDL_image could not initialize ! SDL image Error" << IMG_GetError() << std::endl;
					success = false;
				}
			}
		}
	}
	return success;
}
SDL_Texture *loadTexture(std::string path, SDL_Renderer *&gRenderer)
{
	// the final texture
	SDL_Texture *newTexture = NULL;
	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image " << path.c_str() << " SDL_image Error " << IMG_GetError() << std::endl;
	}
	else
	{
		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unale to create texture from " << path.c_str() << " SDL Error " << SDL_GetError() << std::endl;
		}
		// Get Rid of old loadded surface
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}
bool loadMedia(SDL_Renderer *&gRenderer)
{
	bool success = true;
	// Load PNG texture
	gTexture = loadTexture("image.png", gRenderer);
	if (gTexture == NULL)
	{
		std::cout << "Failed to load texture image !\n";
		success = false;
	}
	return success;
}
void close(SDL_Renderer *&gRenderer)
{
	// Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// Quit SDL subsystem
	IMG_Quit();
	SDL_Quit();
}