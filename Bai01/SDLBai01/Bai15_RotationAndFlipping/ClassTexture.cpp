#include "ClassTexture.h"

ClassTexture::ClassTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}
ClassTexture::~ClassTexture()
{
	free();
}
void ClassTexture::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
int ClassTexture::getWidth() const
{
	return this->mWidth;
}
int ClassTexture::getHeight() const
{
	return this->mHeight;
}
void ClassTexture::setBlendeMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(mTexture, blending);
}
void ClassTexture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture, alpha);
}
void ClassTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}
bool ClassTexture::loadFromFile(SDL_Renderer *gRenderer, std::string path)
{
	free();
	SDL_Texture *newTexture = NULL;
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image ! "<<path.c_str()<< std::endl;
	}
	else
	{
		// set Color key
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create Texture " << SDL_GetError() << std::endl;
		}
		else
		{
			this->mWidth = loadedSurface->w;
			this->mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
		loadedSurface = NULL;
	}
	mTexture = newTexture;
	newTexture = NULL;
	return mTexture != NULL;
}
void ClassTexture::render(SDL_Renderer *gRenderer, int x, int y, SDL_Rect *clip)
{
	// sử dụng SDL_Rect chứa giá trị x,y,w,h của texture
	SDL_Rect renderQuad = { x,y,mWidth,mHeight };
	// nếu clip ( khung hình muốn cắt ) khác NULL gán giá trị w,h cho renderQuad
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	// sử dụng RenderCopy để đưa Texture vào Renderer 
	// giá trị tại clip = NULL thì sẽ full Texture còn khác NULL sẽ lấy tại vị trí x,y và w,h của Texture tương ứng clip đó
	// RenderQuad là vị trí sẽ vẽ Texture tương ứng với x,y,w,h
	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}