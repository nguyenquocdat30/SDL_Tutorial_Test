#include "LTexture.h"
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

LTexture gSpriteSheetTexture;
SDL_Rect gSpriteClip[5];
int main(int argc,char *args[])
{
	if (!init())
	{
		std::cout << "Failed to initialize ! \n";
	}
	else
	{
		if (!loadMedia())
		{
			std::cout << "Failed to load image \n";
		}
		else
		{
			SDL_Event e;
			bool quit = false;
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
				SDL_RenderClear(gRenderer);
				// render top left sprite
				gSpriteSheetTexture.render(0, 0, gRenderer, &gSpriteClip[0]);
				// render top right sprite
				gSpriteSheetTexture.render(SCREEN_WIDTH - 100, 0, gRenderer, &gSpriteClip[1]);
				// render bottom left sprite
				gSpriteSheetTexture.render(0, SCREEN_HEIGHT - 100, gRenderer, &gSpriteClip[2]);
				// render bottom right sprite
				gSpriteSheetTexture.render(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100, gRenderer, &gSpriteClip[3]);
				SDL_RenderPresent(gRenderer);
			}
		}
	}
	close();
	return 0;
}

void close()
{
	// giải phóng
	gSpriteSheetTexture.free();
	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize SDL Error " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning : linear texture filtering not enable!\n";
		}
		gWindow = SDL_CreateWindow("CLIP RENDERING", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			std::cout << "Window could not be created : SDL Error " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				std::cout << "Renderer could not be created ! SDL Error " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					std::cout << "SDL Image could not initialize . SDL image Error " << IMG_GetError() << std::endl;
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
	if (!gSpriteSheetTexture.loadFromFile(gRenderer, "dots.png"))
	{
		std::cout << "Failed to load sprite sheet texture \n";
		success = false;
	}
	else
	{
		gSpriteClip[0].x = 0;
		gSpriteClip[0].y = 0;
		gSpriteClip[0].w = 100;
		gSpriteClip[0].h = 100;

		gSpriteClip[1].x = 100;
		gSpriteClip[1].y = 0;
		gSpriteClip[1].w = 100;
		gSpriteClip[1].h = 100;

		gSpriteClip[2].x = 0;
		gSpriteClip[2].y = 100;
		gSpriteClip[2].w = 100;
		gSpriteClip[2].h = 100;

		gSpriteClip[3].x = 100;
		gSpriteClip[3].y = 100;
		gSpriteClip[3].w = 100;
		gSpriteClip[3].h = 100;
	}
	return success;
}