#include "LTexture1.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int WALKING_ANIMATION_FRAMES = 4;
bool init();
bool loadMedia();
void close();

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
// bai 13
LTexture1 gModulatedTexture;
LTexture1 gBackgroundTexture;

// bai 14
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
LTexture1 gSpriteSheetTexture;

int main(int argc,char *args[])
{
	if (!init())
	{
		std::cout << "Failed to initialize \n";
	}
	else
	{
		if (!loadMedia())
		{
			std::cout << "Failed to load media \n";
		}
		else
		{
			bool quit = false;
			SDL_Event e;
			Uint8 r = 255;
			Uint8 g = 255;
			Uint8 b = 255;
			Uint8 a = 255;
			int frame = 0;
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					/*else if(e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_q: 
							if (a + 32 > 255)
							{
								a = 255;
							}
							else
							{
								a += 32;
							}
							r++;
							break;
						case SDLK_w:
							if (a - 32 < 0)
							{
								a = 0;
							}
							else
							{
								a -= 32;
							}
							g++;
							break;
						case SDLK_e:
							b++;
							break;
						case SDLK_a:
							r--;
							break;
						case SDLK_s:
							g--;
							break;
						case SDLK_d:
							b--;
							break;
						}
					}*/
					
				}
				// to do bai 12
				/*SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				gModulatedTexture.setColor(gRenderer, r, g, b);
				gModulatedTexture.render(gRenderer,0, 0);

				SDL_RenderPresent(gRenderer);*/
				//==========================
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				// to do 13

				gBackgroundTexture.render(gRenderer, 0, 0);


				//gModulatedTexture.setAlpha(a);
				//gModulatedTexture.render(gRenderer, 0, 0);

				// to do 14
				SDL_Rect *currentClip = &gSpriteClips[frame / 4];
				gSpriteSheetTexture.render(gRenderer, (SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2, currentClip);
				++frame;
				if (frame / 4 >= WALKING_ANIMATION_FRAMES)
				{
					frame = 0;
				}
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
		success = false;
	}
	else
	{
		if (!SDL_SetHint("SDL_HINT_RENDER_SCALE_QUALITY", "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}
		gWindow = SDL_CreateWindow("Color modulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags)&imgFlags))
				{
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
	// to do 12
	/*if (!gModulatedTexture.loadFromFile(gRenderer, "colors.png"))
	{
		success = false;
	}*/
	// cau 13
	if (!gModulatedTexture.loadFromFile(gRenderer, "fadeout.png"))
	{
		success = false;
	}
	else
	{
		// alpha blending
		gModulatedTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	}

	if (!gBackgroundTexture.loadFromFile(gRenderer, "fadein.png"))
	{
		success = false;
	}
	// to do 14 animation
	if (!gSpriteSheetTexture.loadFromFile(gRenderer, "foo.png"))
	{
		success = false;
	}
	else
	{
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 64;
		gSpriteClips[0].h = 205;

		gSpriteClips[1].x = 64;
		gSpriteClips[1].y = 0;
		gSpriteClips[1].w = 64;
		gSpriteClips[1].h = 205;

		gSpriteClips[2].x = 128;
		gSpriteClips[2].y = 0;
		gSpriteClips[2].w = 64;
		gSpriteClips[2].h = 205;

		gSpriteClips[3].x = 196;
		gSpriteClips[3].y = 0;
		gSpriteClips[3].w = 64;
		gSpriteClips[3].h = 205;
	}
	return success;
}
void close()
{
	gModulatedTexture.free();
	gBackgroundTexture.free();
	gSpriteSheetTexture.free();
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}