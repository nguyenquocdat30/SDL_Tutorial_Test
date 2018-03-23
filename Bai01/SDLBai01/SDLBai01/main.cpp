#include <iostream>
#include <SDL.h>
// hằng số kích thước màn hình
// screen dimension constants 
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	// The window we will be rendering to
	// Cửa sổ chúng tôi sẽ hiển thị
	SDL_Window *window = NULL;
	// The Surface contained by the window
	// bề mặt của cửa sổ
	SDL_Surface *screenSurface = NULL;

	// Khởi tạo SDL
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error :" << SDL_GetError() << std::endl;
	}
	else
	{
		// Tạo cửa sổ
		// Create window
		window = SDL_CreateWindow("Title SDL Tutorial",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			std::cout << "Window could not be created ! SDL_Error :" << SDL_GetError << std::endl;
		}
		else
		{
			// Lấy bề mặt cửa sổ
			// Get window surface
			screenSurface = SDL_GetWindowSurface(window);
			// Fill the surface white
			// đổ màu trắng lên bề mặt(surface)
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0xFF));
			// Update the surface
			// Cập nhật bề mặt
			SDL_UpdateWindowSurface(window);
			// Wait five seconds
			// chờ 5 giây
			SDL_Delay(5000);
		}
	}
	/*SDL_FreeSurface(screenSurface);
	screenSurface = NULL;*/
	// Hủy bỏ cửa sổ
	// Destroy window
	SDL_DestroyWindow(window);
	// Thoát các hệ thống con SDL
	// Quit SDL subsystems
	SDL_Quit();
	return 0;
}