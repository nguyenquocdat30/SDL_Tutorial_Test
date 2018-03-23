#pragma once
#ifndef __INITSDL_H_
#define __INITSDL_H_
#include "ClassTexture.h"

class InitSDL
{
private:
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	SDL_Window *gWindow;
	SDL_Renderer *gRenderer;
public:
	InitSDL();
	~InitSDL();
	bool init();
	bool loadMedia();
	void free();
	void Run();
};
#endif // !__INITSDL_H_