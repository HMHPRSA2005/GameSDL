#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
	width_frame = 0;
	height_frame = 0;
	x_move = 0;
	y_move = 0;
	x_now = 0;
	y_now = 0;
	on_the_ground = false;
	comeback_time = 0;
	frame = 0;

	animation_left = 0;
	animation_right = 0;
	input_type.left = 1;
	type_move = STATIC_ENEMY;
}

Enemy::~Enemy()
{
	Free();
}

bool Enemy::LoadImg(std::string link, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(link, screen);
	if (ret)
	{
		width_frame = rect.w / 12;
		height_frame = rect.h;
	}

	return ret;
}

SDL_Rect Enemy::GetRectFrame()
{
	SDL_Rect _rect;
	_rect.x = rect.x;
	_rect.y = rect.y;
	_rect.w = rect.w / 12;
	_rect.h = rect.h / 12;

	return _rect;
}

void Enemy::set_clip()
{
	if (width_frame > 0 && height_frame > 0)
	{
		frame_clip[0].x = 0;
		frame_clip[0].y = 0;
		frame_clip[0].w = width_frame;
		frame_clip[0].h = height_frame;

		frame_clip[1].x = width_frame;
		frame_clip[1].y = 0;
		frame_clip[1].w = width_frame;
		frame_clip[1].h = height_frame;

		frame_clip[2].x = 2 * width_frame;
		frame_clip[2].y = 0;
		frame_clip[2].w = width_frame;
		frame_clip[2].h = height_frame;

		frame_clip[3].x = 3 * width_frame;
		frame_clip[3].y = 0;
		frame_clip[3].w = width_frame;
		frame_clip[3].h = height_frame;

		frame_clip[4].x = 4 * width_frame;
		frame_clip[4].y = 0;
		frame_clip[4].w = width_frame;
		frame_clip[4].h = height_frame;

		frame_clip[5].x = 5 * width_frame;
		frame_clip[5].y = 0;
		frame_clip[5].w = width_frame;
		frame_clip[5].h = height_frame;

		frame_clip[6].x = 6 * width_frame;
		frame_clip[6].y = 0;
		frame_clip[6].w = width_frame;
		frame_clip[6].h = height_frame;

		frame_clip[7].x = 7 * width_frame;
		frame_clip[7].y = 0;
		frame_clip[7].w = width_frame;
		frame_clip[7].h = height_frame;

		frame_clip[8].x = 8 * width_frame;
		frame_clip[8].y = 0;
		frame_clip[8].w = width_frame;
		frame_clip[8].h = height_frame;

		frame_clip[9].x = 9 * width_frame;
		frame_clip[9].y = 0;
		frame_clip[9].w = width_frame;
		frame_clip[9].h = height_frame;

		frame_clip[10].x = 10 * width_frame;
		frame_clip[10].y = 0;
		frame_clip[10].w = width_frame;
		frame_clip[10].h = height_frame;

		frame_clip[11].x = 11 * width_frame;
		frame_clip[11].y = 0;
		frame_clip[11].w = width_frame;
		frame_clip[11].h = height_frame;
	}
}

void Enemy::Show(SDL_Renderer* des)
{
	if (comeback_time == 0)
	{
		rect.x = x_now - map_x;
		rect.y = y_now - map_y;
		frame++;

		if (frame >= 12)
		{
			frame = 0;
		}

		SDL_Rect* now_clip = &frame_clip[frame];

		SDL_Rect renderQuad = { rect.x, rect.y, width_frame, width_frame };

		SDL_RenderCopy(des, p_object, now_clip, &renderQuad);
	}
}

void Enemy::InitEnemy()
{
	x_move = 0;
	y_move = 0;
	if (x_now > 300)
	{
		x_now -= 300;
		animation_left -= 300;
		animation_right -= 300;
	}
	y_now = 0;
	comeback_time = 0;
	input_type.left = 1;
}

void Enemy::DoPlayer(Map& map_data)
{
	if (comeback_time == 0)
	{
		x_move = 0;
		y_move += GRAVITY_SPEED;
		if (y_move >= 10)
		{
			y_move = MAX_FALL_SPEED;
		}

		if (input_type.left == 1)
		{
			x_move -= ENEMY_SPEED;
		}
		else if (input_type.right == 1)
		{
			x_move += ENEMY_SPEED;
		}

		CheckMap(map_data);
	}
	else if (comeback_time > 0)
	{
		comeback_time--;
		if (comeback_time == 0)
		{
			InitEnemy();
		}
	}
}

void Enemy::CheckMap(Map& map_data)
{
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;

	int height_min = min(height_frame, square_size);

	x1 = (x_now + x_move) / square_size;
	x2 = (x_now + x_move + width_frame - 1) / square_size;

	y1 = y_now / square_size;
	y2 = (y_now + height_min - 1) / square_size;

	if (x1 >= 0 && x2 < total_square_x && y1 >= 0 && y2 < total_square_y)
	{
		if (x_move > 0) // ke thu di chuyen sang phai
		{
			int value1 = map_data.map[y1][x2];
			int value2 = map_data.map[y2][x2];

				if ((value1 != 0 && value1 != 3 && value1 != 4 && value1 != 5 && value1 != 7 && value1 != 8 && value1 != 9) || (value2 != 0 && value2 != 3 && value2 != 4 && value2 != 5 && value2 != 7 && value2 != 8 && value2 != 9))
				{
					x_now = x2 * square_size;
					x_now -= width_frame + 1;
					x_move = 0;
				}
		}
		else if (x_move < 0) // ke thu di chuyen sang trai
		{
			int value1 = map_data.map[y1][x1];
			int value2 = map_data.map[y2][x1];

				if ((value1 != 0 && value1 != 3 && value1 != 4 && value1 != 5 && value1 != 7 && value1 != 8 && value1 != 9) || (value2 != 0 && value2 != 3 && value2 != 4 && value2 != 5 && value2 != 7 && value2 != 8 && value2 != 9))
				{
					x_now = (x1 + 1) * square_size;
					x_move = 0;
				}
		}
	}

	int width_min = min(width_frame, square_size);

	x1 = x_now / square_size;
	x2 = (x_now + width_min) / square_size;

	y1 = (y_now + y_move) / square_size;
	y2 = (y_now + y_move + height_frame - 1) / square_size;

	if (x1 >= 0 && x2 <= total_square_x && y1 >= 0 && y2 <= total_square_y);
	{
		if (y_move > 0) // ke thu roi
		{
			int value1 = map_data.map[y2][x1];
			int value2 = map_data.map[y2][x2];

				if ((value1 != 0 && value1 != 3 && value1 != 4 && value1 != 5 && value1 != 7 && value1 != 8 && value1 != 9) || (value2 != 0 && value2 != 3 && value2 != 4 && value2 != 5 && value2 != 7 && value2 != 8 && value2 != 9))
				{
					y_now = y2 * square_size;
					y_now -= (height_frame + 1);
					y_move = 0;
					on_the_ground = true;
				}
		}
	}

	x_now += x_move;
	y_now += y_move;

	if (x_now < 0)
	{
		x_now = 0;
	}
	else if (x_now + width_frame > map_data.total_x)
	{
		x_now = map_data.total_x - width_frame - 1;
	}

	if (y_now > map_data.total_y)
	{
		comeback_time = 40;
	}
}

void Enemy::ImpMoveType(SDL_Renderer* screen)
{
		if (on_the_ground == true)
		{
			if (x_now > animation_right)
			{
				input_type.left = 1;
				input_type.right = 0;
				LoadImg("image//enemy_left.png", screen);
			}
			else if (x_now < animation_left)
			{
				input_type.left = 0;
				input_type.right = 1;
				LoadImg("image//enemy_right.png", screen);
			}
		}
		else
		{
			if (input_type.left == 1)
			{
				LoadImg("image//enemy_left.png", screen);
			}
		}
}

void Enemy::ImpMoveTypeOther(SDL_Renderer* screen)
{
	if (on_the_ground == true)
	{
		if (x_now > animation_right)
		{
			input_type.left = 1;
			input_type.right = 0;
			LoadImg("image//other_enemy_left.png", screen);
		}
		else if (x_now < animation_left)
		{
			input_type.left = 0;
			input_type.right = 1;
			LoadImg("image//other_enemy_right.png", screen);
		}
	}
	else
	{
		if (input_type.left == 1)
		{
			LoadImg("image//other_enemy_left.png", screen);
		}
	}
}

void Enemy::InitBullet(Bullet* bullet, SDL_Renderer* screen)
{
	if (bullet != NULL)
	{
		bullet->LoadImg("image//bullet.png", screen);
		bullet->set_is_move(true);
		bullet->set_bullet_direction(Bullet::DIRECTION_LEFT);
		bullet->SetRect(rect.x + 20, rect.y + 0);
		bullet->set_x_move(10);
		bullet_list.push_back(bullet);
	}
}

void Enemy::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
	for (int i = 0; i < bullet_list.size(); i++)
	{
		Bullet* bullet = bullet_list.at(i);
		if (bullet != NULL)
		{
			if (bullet->get_is_move())
			{
				int bullet_space = rect.x + width_frame - bullet->GetRect().x;
				if (bullet_space > 0 && bullet_space < 200)
				{
					bullet->HandleMove(x_limit, y_limit);
					bullet->Render(screen);
				}
				else
				{
					bullet->set_is_move(false);
				}
			}
			else
			{
				bullet->set_is_move(true);
				bullet->SetRect(rect.x + 20, rect.y + 0);
			}
		}
	}
}

void Enemy::RemoveBullet(const int& index)
{
	int size = bullet_list.size();
	if (size > 0 && index < size)
	{
		Bullet* bullet = bullet_list.at(index);
		bullet_list.erase(bullet_list.begin() + index);

		if (bullet)
		{
			delete bullet;
			bullet = NULL;
		}
	}
}