#include <iostream>
#include <SDL.h>
// tối ưu hóa bề mặt và kéo dãn ảnh ra phù hợp với màn hình hiển thị
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Key press surfaces constants
enum KeyPressSurface
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

// the window we'll be rendering to
SDL_Window *gWindow = NULL;
// The surface contained by window
SDL_Surface *gScreenWindow = NULL;

// Starts up SDL and creates window
bool init();
// Loads media
bool loadMedia();
// Frees media and shuts down SDL
void close();
// Loads individual image
// 1 hàm để loadSurface thông qua đường dẫn path
SDL_Surface *loadSurface(std::string path);
// The images that correspond to a keypress
// 1 mảng chứa các surface
SDL_Surface *gKeyPressSurface[KEY_PRESS_SURFACE_TOTAL];
// Current displayed image
SDL_Surface *gCurrentSurface = NULL;
int main(int argc, char *args[])
{
	bool quit = false;
	SDL_Event e;
	// set default current surface
	gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
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
				// Handle event on queue
				while (SDL_PollEvent(&e) != 0)
				{
					// User request quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					// User presses a key
					else if (e.type = SDL_KEYDOWN)
					{
						// Select surfaces based on key press
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_UP];
							break;
						case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DOWN];
							break;
						case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_LEFT];
							break;
						case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT];
							break;
						default:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
							break;
						}
					}
				}
				// to do
				SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = SCREEN_WIDTH;
				stretchRect.h = SCREEN_HEIGHT;
				// Apply image stretched
				SDL_BlitScaled(gCurrentSurface, NULL, gScreenWindow,&stretchRect);
				// Apply the current image
				//SDL_BlitSurface(gCurrentSurface, NULL, gScreenWindow, NULL);
				// Update the surface
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
		gWindow = SDL_CreateWindow("Key Press", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			std::cout << "Window could not be created! SDL_Error : " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			// get window surface
			gScreenWindow = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}
//==============================
SDL_Surface *loadSurface(std::string path)
{
	// The final optimized image
	SDL_Surface *optimizedSurface = NULL;
	// Load image at specified path
	SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image " << path.c_str() << " SDL Error :" << SDL_GetError() << std::endl;
	}
	else
	{
		// Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenWindow->format, NULL);
		if (optimizedSurface == NULL)
		{
			std::cout << "Unable to optimize image " << path.c_str() << "SDL Error : " << SDL_GetError() << std::endl;
		}
		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
		loadedSurface = NULL;
	}
	return optimizedSurface;
}
bool loadMedia()
{
	bool success = true;
	// Load default surface
	gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("Image/portal1.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		std::cout << "Failed to load default image! \n";
		success = false;
	}
	// Load Up surface
	gKeyPressSurface[KEY_PRESS_SURFACE_UP] = loadSurface("Image/portal1.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_UP] == NULL)
	{
		std::cout << "Failed to load up image! \n";
		success = false;
	}
	// Load down surface
	gKeyPressSurface[KEY_PRESS_SURFACE_DOWN] = loadSurface("Image/portal1.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		std::cout << "Failed to load down image! \n";
		success = false;
	}
	// Load left surface
	gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] = loadSurface("Image/portal1.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		std::cout << "Failed to load left image! \n";
		success = false;
	}
	// Load right surface
	gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT] = loadSurface("Image/portal1.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT] == NULL)
	{
		std::cout << "Failed to load right image! \n";
		success = false;
	}
	return success;
}
void close()
{
	// Deallocate surface
	for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
	{
		SDL_FreeSurface(gKeyPressSurface[i]);
		gKeyPressSurface[i] = NULL;
	}
	// Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gCurrentSurface = NULL;
	gScreenWindow = NULL;
	// Quit SDL subsystems
	SDL_Quit();
}