#pragma once
#ifndef __TEXTURE_H_
#define __TEXTURE_H_
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
class LTexture1
{
public:
	LTexture1();
	~LTexture1();
	bool loadFromFile(SDL_Renderer *gRenderer, std::string path);
	void free();
	void render(SDL_Renderer *gRenderer, int x, int y, SDL_Rect *clip = NULL);
	void setColor(SDL_Renderer *gRenderer, Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode(SDL_BlendMode blending);
	void setAlpha(Uint8 alpha);
	int getWidth();
	int getHeight();
private:
	int width;
	int height;
	SDL_Texture *mTexture;
};


#endif // !__TEXTURE_H_