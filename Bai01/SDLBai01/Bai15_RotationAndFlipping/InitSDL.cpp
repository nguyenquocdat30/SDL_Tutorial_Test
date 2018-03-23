#include "InitSDL.h"

bool InitSDL::init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL Could not Initialize ! SDL Error " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		if (!SDL_SetHint("SDL_HINT_RENDER_SCALE_QUALITY", "1"))
		{
			std::cout << "Warning linear Texture filtering not enable !\n";
			success = false;
		}
		gWindow = SDL_CreateWindow("Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			std::cout << "Windows could not be created ! SDL Error"<<SDL_GetError()<<std::endl;
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				std::cout << "Renderer could not be created ! SDL Error !" << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags)&imgFlags))
				{
					std::cout << "IMG could not initilize ! IMG Error! " << IMG_GetError() << std::endl;
					success = false;
				}
			}
		}
	}
	return success;
}
bool InitSDL::loadMedia()
{
	bool success = true;
	// Load các media tại đây

	//=============================
	return success;
}
void InitSDL::free()
{
	// Giải phóng bộ nhớ được cấp phát sau này tại đây

	//=============================
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}
InitSDL::InitSDL():SCREEN_WIDTH(640),SCREEN_HEIGHT(480)
{
	gWindow = NULL;
	gRenderer = NULL;
}
InitSDL::~InitSDL()
{
	free();
}
void InitSDL::Run()
{
	if (!init())
	{
		std::cout << "Failed to initilize !\n";
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
			}
		}
	}
	free();
}