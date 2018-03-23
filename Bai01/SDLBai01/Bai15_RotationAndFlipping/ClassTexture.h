#pragma once
#ifndef __CLASSTEXTURE_H_
#define __CLASSTEXTURE_H_
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class ClassTexture
{
private:
	SDL_Texture *mTexture;
	int mWidth;
	int mHeight;
public:
	ClassTexture();
	~ClassTexture();
	// hàm lấy giá trị width và height
	int getWidth()const;
	int getHeight()const;
	// Hàm Load hình ảnh vào texture
	bool loadFromFile(SDL_Renderer *gRenderer, std::string path);
	// Hàm render - vẽ lên màn hình
	void render(SDL_Renderer *gRenderer, int x, int y, SDL_Rect *clip = NULL);
	// Hàm xét giá trị alpha cho Texture , alpha càng nhỏ Texture càng mờ
	void setAlpha(Uint8 alpha);
	// Hàm xử dụng để kích hoạt tính năng trộn alpha
	void setBlendeMode(SDL_BlendMode blending);
	// Hàm xét giá trị màu cho Texture
	void setColor(Uint8 red,Uint8 green,Uint8 blue);
	// Hàm giải phóng vùng nhớ đã cấp phát
	void free();
};

#endif // !__CLASSTEXTURE_H_