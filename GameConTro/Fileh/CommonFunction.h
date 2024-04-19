#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include <SDL_image.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Window* game_window = NULL;
static SDL_Renderer* game_screen = NULL;
static SDL_Event game_event;

// Game screen
const int FRAME_PER_SECOND = 40;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 832;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

#define square_size 64

#define total_square_x 400
#define total_square_y 13

typedef struct Input
{
	int left;
	int right;
	int up;
	int down;
	int jump;
};

typedef struct Map
{
	int start_x;
	int start_y;

	int total_x;
	int total_y;

	int map[total_square_y][total_square_x];
	char* file_name;
};

namespace SDLCommonFunction
{
	bool CheckImpact(const SDL_Rect& object1, const SDL_Rect& object2);
	bool CheckMousePos(const int& x, const int& y, const SDL_Rect& object);
}
