#pragma once

#include "CommonFunction.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void SetRect(const int& x, const int& y) { rect.x = x, rect.y = y; }
	SDL_Rect GetRect() const { return rect;}
	SDL_Texture* GetObject() const { return p_object;}

	virtual bool LoadImg(std::string link, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();
protected:
	SDL_Texture* p_object; // luu tru hinh anh
	SDL_Rect rect;         // luu tru kich thuoc
};
