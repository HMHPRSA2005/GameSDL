#pragma once

#include "CommonFunction.h"
#include "BaseObject.h"

class TileMap : public BaseObject
{
public:
	TileMap() { ; }
	~TileMap() { ; }
};

class GameMap
{
public:
	GameMap() {;}
	~GameMap() {;}

	void LoadMap(const char* name);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
	Map getMap() const { return game_map; };
	void SetMap(Map& map_data) { game_map = map_data; };
private:
	Map game_map;
	TileMap tile_map[20];
};