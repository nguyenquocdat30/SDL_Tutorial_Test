#include "LTexture1.h"

LTexture1::LTexture1()
{
	mTexture = NULL;
	width = 0;
	height = 0;
}

LTexture1::~LTexture1()
{
	free();
}
bool LTexture1::loadFromFile(SDL_Renderer *gRenderer, std::string path)
{
	free();

	SDL_Texture *newTexture = NULL;

	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image " << std::endl;
	}
	else
	{
		SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,0x00,0xFF,0xFF));
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture\n";
		}
		else
		{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
		loadedSurface = NULL;
	}
	mTexture = newTexture;
	return mTexture != NULL;
}
void LTexture1::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		this->width = 0;
		this->height = 0;
	}
}
void LTexture1::render(SDL_Renderer *gRenderer, int x, int y, SDL_Rect *clip)
{
	SDL_Rect renderQuad = { x,y,width,height };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}
void LTexture1::setColor(SDL_Renderer *gRenderer, Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}
void LTexture1::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(mTexture, blending);
}
void LTexture1::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture, alpha);
}
int LTexture1::getHeight()
{
	return this->height;
}
int LTexture1::getWidth()
{
	return this->width;
}
