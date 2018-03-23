#pragma once
#ifndef __LTEXTURE_H_
#define __LTEXTURE_H_
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
class LTexture
{
public:
	// hàm dựng - khởi tạo
	LTexture();
	// Hàm hủy 
	~LTexture();
	// Load 1 hình ảnh lên từ 1 đường dẫn file đưa vào Renderer để vẽ
	bool loadFromFile(SDL_Renderer *gRenderer, std::string path);
	// Giải phóng cấp phát
	void free();
	// vẽ Texture lên tại tọa độ x,y với diện tích bằng 1 hình chữ nhật clip. NULL nếu là full hình
	void render(int x, int y, SDL_Renderer *gRenderer, SDL_Rect *clip = NULL);
	// getter giá trị width và height
	int getWidth();
	int getHeight();
private:
	SDL_Texture *gTexture;
	int width;
	int height;
};

#endif // !__LTEXTURE_H_