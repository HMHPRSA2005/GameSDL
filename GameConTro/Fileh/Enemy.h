#pragma once

#include "CommonFunction.h"
#include "BaseObject.h"
#include "Bullet.h"

#define GRAVITY_SPEED 1;
#define MAX_FALL_SPEED 10;
#define ENEMY_SPEED 2;

class Enemy : public BaseObject
{
private:
	int map_x;
	int map_y;
	bool on_the_ground;
	int comeback_time;
	float x_now;
	float y_now;
	float x_move;
	float y_move;
	SDL_Rect frame_clip[12];
	int frame;
	int width_frame;
	int height_frame;

	int type_move;
	int animation_left;
	int animation_right;
	Input input_type;

	std::vector<Bullet*> bullet_list;

public:
	Enemy();
	~Enemy();

	enum TypeMove
	{
		STATIC_ENEMY = 0,
		MOVE_IN_SPACE_ENEMY = 1,
	};

	void set_x_move(const float& xMove) { x_move = xMove; }
	void set_y_move(const float& yMove) { y_move = yMove; }

	void set_x_now(const float& xNow) { x_now = xNow; }
	void set_y_now(const float& yNow) { y_now = yNow; }
	float get_x_now() const { return x_now; }
	float get_y_now() const { return y_now; }
	void SetMapXY(const int& mapx, const int& mapy) { map_x = mapx; map_y = mapy; }

	void set_clip();
	bool LoadImg(std::string link, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	int get_width_frame() const { return width_frame;}
	int get_height_frame() const { return height_frame; }
	void DoPlayer(Map& map_data);
	void CheckMap(Map& map_data);
	void InitEnemy();
	SDL_Rect GetRectFrame();

	void set_type_move(const int& typeMove) { type_move = typeMove; }
	void set_animation(const int& now_left, const int& now_right) { animation_left = now_left, animation_right = now_right; }
	void set_input_left(const int& inputLeft) { input_type.left = inputLeft; }
	void ImpMoveType(SDL_Renderer* screen);
	void ImpMoveTypeOther(SDL_Renderer* screen);

	std::vector<Bullet*> get_bullet_list() const { return bullet_list; }
	void set_bullet_list(const std::vector<Bullet*>& bulletList) { bullet_list = bulletList; }
	void InitBullet(Bullet* bullet, SDL_Renderer* screen);
	void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit);
	void RemoveBullet(const int& index);
};