#include "LTexture.h"

// Constructor
LTexture::LTexture()
{
	// Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

// Destructor
LTexture::~LTexture()
{
	// Deallocate
	free();
}
bool LTexture::loadFromFile(std::string path, SDL_Renderer *gRenderer)
{
	// Get rid of preexisting texture
	free();
	// The final Texture
	SDL_Texture *newTexture = NULL;
	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image from" << path.c_str() << " SDL_Image Error ! " << IMG_GetError() << std::endl;
	}
	else
	{
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x00, 0xFF, 0xFF));
		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create Texture from " << path.c_str() << " SDL Error ! " << SDL_GetError() << std::endl;
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
		loadedSurface = NULL;
	}
	mTexture = newTexture;
	newTexture = NULL;
	return mTexture != NULL;
}
void LTexture::free()
{
	// free Texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
void LTexture::render(int x, int y, SDL_Renderer *gRenderer)
{
	// Set rendering space and render to screen
	SDL_Rect renderQuad = { x,y,mWidth,mHeight };
	SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}
int LTexture::getWidth()
{
	return mWidth;
}
int LTexture::getHeight()
{
	return mHeight;
}
