#include "stdafx.h"
#include "map.h"
#include <bits/stdc.h>

void GameMap::LoadMap(const char* name)
{
	FILE* file = NULL;
	fopen_s(&file, name, "rb");
	if (file == NULL)
	{
		return;
	}

	game_map.total_x = 0;
	game_map.total_y = 0;

	for (int i = 0; i < total_square_y; i++)
	{
		for (int j = 0; j < total_square_x; j++)
		{
			fscanf_s(file, "%d", &game_map.map[i][j]);
			int value = game_map.map[i][j];
			if (value > 0)
			{
				if (j > game_map.total_x)
				{
					game_map.total_x = j;
				}

				if (i > game_map.total_y)
				{
					game_map.total_y = i;
				}
			}
		}
	}

	game_map.total_x = (game_map.total_x + 1) * square_size;
	game_map.total_y = (game_map.total_y + 1) * square_size;

	game_map.start_x = 0;
	game_map.start_y = 0;
	
	fclose(file);
}


void GameMap::LoadTiles(SDL_Renderer* screen)
{
	char file_image[30];
	FILE* file = NULL;

	for (int i = 0; i < 10; i++) {
		sprintf_s(file_image, "map/%d.png", i);

		fopen_s(&file, file_image, "rb");
		if (file == NULL)
		{
			continue;
		}

		fclose(file);

		tile_map[i].LoadImg(file_image, screen);
	}
}

void GameMap::DrawMap(SDL_Renderer* screen)
{
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;

	int map_x = 0;
	int map_y = 0;

	map_x = game_map.start_x / square_size;

	x1 = (game_map.start_x % square_size) * (-1);
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : square_size);

	map_y = game_map.start_y / square_size;

	y1 = (game_map.start_y % square_size) * (-1);
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : square_size);

	for (int i = y1; i < y2; i += square_size) {
		map_x = game_map.start_x / square_size;
		for (int j = x1; j < x2; j += square_size)
		{
			int value = game_map.map[map_y][map_x];
			if (value > 0)
			{
				tile_map[value].SetRect(j, i);
				tile_map[value].Render(screen);
			}
			map_x++;
		}
		map_y++;
	}
}