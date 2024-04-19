#pragma once

#include "CommonFunction.h"

class Text
{
private:
	std::string content;
	SDL_Color text_color;
	SDL_Texture* texture;
	int width;
	int height;

public:
	Text();
	~Text();

	enum TextColor
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
	};

	bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
	void Free();

	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetColor(int type);

	void RenderText(SDL_Renderer* screen, 
		            int x, int y, 
		            SDL_Rect* clip = NULL, 
		            double angle = 0.0, 
		            SDL_Point* center = NULL, 
		            SDL_RendererFlip flip = SDL_FLIP_NONE);

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

	void SetText(const std::string& text) { content = text; }
	std::string GetText() const { return content; }
};
