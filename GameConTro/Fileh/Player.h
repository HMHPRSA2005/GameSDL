#pragma once

#include "CommonFunction.h"
#include "BaseObject.h"
#include "Bullet.h"

#define GRAVITY_SPEED 1;
#define MAX_FALL_SPEED 10;
#define PLAYER_SPEED 6;
#define PLAYER_JUMP 20;

class Player : public BaseObject
{
private:
	std::vector<Bullet*> bullet_list;

	float x_move;
	float y_move;

	float x_now;
	float y_now;

	int width_frame;
	int height_frame;

	SDL_Rect frame_clip[12];
	Input input_type;
	int frame;
	int status_move;
	bool on_the_ground;

	int map_x_;
	int map_y_;

	int comeback_time;
	int money_count;

public:
	Player();
	~Player();

	enum RunType
	{
		RUN_RIGHT = 0,
		RUN_LEFT = 1,
	};

	bool LoadImg(std::string link, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void KeyBoard(SDL_Event events, SDL_Renderer* screen);
	void set_clip();

	void DoPlayer(Map& map_data);
	void CheckMap(Map& map_data);
	void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; }
	void CenterMap(Map& map_data);
	SDL_Rect GetRectFrame();

	void set_bullet_list(std::vector<Bullet*> bullet_list_) { bullet_list = bullet_list_; }
	std::vector<Bullet*> get_bullet_list() const { return bullet_list; }
	void HandleBullet(SDL_Renderer* des);
	void RemoveBullet(const int& index);
	void set_comeback_time(const int& come_back_time) { comeback_time = come_back_time; }
	void Money();
	int GetMoneyCount() const { return money_count; }
};
