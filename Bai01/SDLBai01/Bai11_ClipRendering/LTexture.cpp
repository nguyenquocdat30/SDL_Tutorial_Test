#include "LTexture.h"

LTexture::LTexture()
{
	gTexture = NULL;
	width = 0;
	height = 0;
}
LTexture::~LTexture()
{
	free();
}
void LTexture::free()
{
	if (gTexture != NULL)
	{
		SDL_DestroyTexture(gTexture);
		gTexture = NULL;
		width = 0;
		height = 0;
	}
}
bool LTexture::loadFromFile(SDL_Renderer *gRenderer,std::string path)
{
	free();
	SDL_Texture *newTexture = NULL;
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image :" << path.c_str() << " SDL Image error !" << IMG_GetError() << std::endl;
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x00, 0xFF,0xFF));
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture from " << path.c_str() << "SDL Error ! " << SDL_GetError() << std::endl;
		}
		else
		{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
		loadedSurface = NULL;
	}
	gTexture = newTexture;
	newTexture = NULL;
	return gTexture != NULL;
}
void LTexture::render(int x, int y, SDL_Renderer *gRenderer, SDL_Rect *clip)
{
	SDL_Rect renderQuad = { x,y,width,height };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopy(gRenderer, gTexture, clip, &renderQuad);
}
int LTexture::getWidth()
{
	return width;
}
int LTexture::getHeight()
{
	return height;
}