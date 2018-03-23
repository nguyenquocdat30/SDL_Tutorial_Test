#pragma once
#ifndef __LTEXTURE_H_
#define __LTEXTURE_H_
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
class LTexture
{
public:
	// Initializes variables
	LTexture();
	// Deallocates memory
	~LTexture();
	bool loadFromFile(std::string path,SDL_Renderer *gRenderer);
	// Deallocates texture
	void free();
	// Renderer texture at given point
	void render(int x, int y,SDL_Renderer *gRenderer);
	//gets image dimensions
	int getWidth();
	int getHeight();
private:
	// Image dimensions
	int mWidth;
	int mHeight;
	// The actual hardware texture
	SDL_Texture *mTexture;
	
};
#endif // !__LTEXTURE_H_