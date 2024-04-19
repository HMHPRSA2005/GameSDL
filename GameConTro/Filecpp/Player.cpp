
#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	frame = 0;
	x_now = 0;
	y_now = 0;
	x_move = 0;
	y_move = 0;
	width_frame = 0;
	height_frame = 0;
	status_move = -1;
	input_type.right = 0;
	input_type.left = 0;
	input_type.jump = 0;
	input_type.up = 0;
	input_type.down = 0;
	on_the_ground = false;
	map_x_ = 0;
	map_y_ = 0;
	comeback_time = 0;
	money_count = 0;
}

Player::~Player()
{
	Free();
}

bool Player::LoadImg(std::string link, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(link, screen);

	if (ret == true)
	{
		width_frame = rect.w / 12;
		height_frame = rect.h;
	}

	return ret;
}

SDL_Rect Player::GetRectFrame()
{
	SDL_Rect _rect;
	_rect.x = rect.x;
	_rect.y = rect.y;
	_rect.w = rect.w / 12;
	_rect.h = rect.h / 12;

	return _rect;
}

void Player::set_clip()
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

void Player::Show(SDL_Renderer* des)
{
	if (status_move == RUN_LEFT)
	{
		LoadImg("image//left.png", des);
	}
	else
	{
		LoadImg("image//right.png", des);
	}

	if (input_type.left == 1 || input_type.right == 1)
	{
		frame++;
	}
	else
	{
		frame = 0;
	}

	if (frame >= 12)
	{
		frame = 0;
	}

	rect.x = x_now - map_x_;
	rect.y = y_now - map_y_; 

	SDL_Rect* now_clip = &frame_clip[frame];

	SDL_Rect renderQuad = { rect.x, rect.y, width_frame, height_frame };

	SDL_RenderCopy(des, p_object, now_clip, &renderQuad);
}

void Player::KeyBoard(SDL_Event event, SDL_Renderer* screen)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			status_move = RUN_RIGHT;
			input_type.right = 1;
			input_type.left = 0;
			break;

		case SDLK_LEFT:
			status_move = RUN_LEFT;
			input_type.left = 1;
			input_type.right = 0;
			break;

		case SDLK_UP:
			input_type.jump = 1;
			break;

		case SDLK_f:
			Bullet* bullet = new Bullet();
			bullet->LoadImg("image//bullet.png", screen);

			if (status_move == RUN_RIGHT)
			{
				bullet->set_bullet_direction(Bullet::DIRECTION_RIGHT);
				bullet->SetRect(this->rect.x + width_frame - 20, rect.y + 30);
			}
			else if (status_move == RUN_LEFT)
			{
				bullet->set_bullet_direction(Bullet::DIRECTION_LEFT);
				bullet->SetRect(this->rect.x, rect.y + 30);
			}

			bullet->set_x_move(10);
			bullet->set_is_move(true);

			bullet_list.push_back(bullet);
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			input_type.right = 0;
		    break;

		case SDLK_LEFT:
			input_type.left = 0;
		    break;

		case SDLK_UP:
			input_type.jump = 0;
			break;
		}
	}
}

void Player::HandleBullet(SDL_Renderer* des)
{
	for (int i = 0; i < bullet_list.size(); i++)
	{
		Bullet* bullet = bullet_list.at(i);
		if (bullet != NULL)
		{
			if (bullet->get_is_move() == true)
			{
				bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				bullet->Render(des);
			}
			else
			{
				bullet_list.erase(bullet_list.begin() + i);
				if (bullet != NULL)
				{
					delete bullet;
					bullet = NULL;
				}
			}
		}
	}
}

void Player::RemoveBullet(const int& index)
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

void Player::DoPlayer(Map& map_data)
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
			x_move -= PLAYER_SPEED;
		}
		else if (input_type.right == 1)
		{
			x_move += PLAYER_SPEED;
		}

		if (input_type.jump == 1)
		{
			if (on_the_ground == true)
			{
				y_move = -PLAYER_JUMP;
			}
			on_the_ground = false;
			input_type.jump = 0;
		}

		CheckMap(map_data);
		CenterMap(map_data);
	}
	
	if (comeback_time > 0)
	{
		comeback_time--;
		if (comeback_time == 0)
		{
			x_now -= 200;
			y_now = 0;
			x_move = 0;
			y_move = 0;
		}
	}
}

void Player::CenterMap(Map& map_data)
{
	map_data.start_x = x_now - (SCREEN_WIDTH / 3);
	if (map_data.start_x < 0)
	{
		map_data.start_x = 0;
	}
	else if (map_data.start_x + SCREEN_WIDTH >= map_data.total_x)
	{
		map_data.start_x = map_data.total_x - SCREEN_WIDTH;
	}

	map_data.start_y = y_now - (SCREEN_HEIGHT / 3);
	if (map_data.start_y < 0)
	{
		map_data.start_y = 0;
	}
	else if (map_data.start_y + SCREEN_HEIGHT >= map_data.total_y)
	{
		map_data.start_y = map_data.total_y - SCREEN_HEIGHT;
	}
}

void Player::CheckMap(Map& map_data)
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
		if (x_move > 0) // nhan vat di chuyen sang phai
		{
			int value1 = map_data.map[y1][x2];
			int value2 = map_data.map[y2][x2];

			if (value1 == 9 || value2 == 9)
			{
				map_data.map[y1][x2] = 0;
				map_data.map[y2][x2] = 0;
				Money();
			}
			else if (value1 == 7 || value2 == 7)
			{
				comeback_time = 10;
			}
			else
			{
				if ((value1 != 0 && value1 != 3 && value1 != 4 && value1 != 5 && value1 != 7 && value1 != 8) || (value2 != 0 && value2 != 3 && value2 != 4 && value2 != 5 && value2 != 7 && value2 != 8))
				{
					x_now = x2 * square_size;
					x_now -= width_frame + 1;
					x_move = 0;
				}
			}
		}
		else if (x_move < 0) // nhan vat di chuyen sang trai
		{
			int value1 = map_data.map[y1][x1];
			int value2 = map_data.map[y2][x1];

			if (value1 == 9 || value2 == 9)
			{
				map_data.map[y1][x1] = 0;
				map_data.map[y2][x1] = 0;
				Money();
			}
			else if (value1 == 7 || value2 == 7)
			{
				comeback_time = 10;
			}
			else
			{
				if ((value1 != 0 && value1 != 3 && value1 != 4 && value1 != 5 && value1 != 7 && value1 != 8) || (value2 != 0 && value2 != 3 && value2 != 4 && value2 != 5 && value2 != 7 && value2 != 8))
				{
					x_now = (x1 + 1) * square_size;
					x_move = 0;
				}
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
		if (y_move > 0) // nhan vat roi
		{
			int value1 = map_data.map[y2][x1];
			int value2 = map_data.map[y2][x2];
			if (value1 == 9 || value2 == 9)
			{
				map_data.map[y2][x1] = 0;
				map_data.map[y2][x2] = 0;
				Money();
			}
			else if (value1 == 7 || value2 == 7)
			{
				comeback_time = 10;
			}
			else
			{
				if ((value1 != 0 && value1 != 3 && value1 != 4 && value1 != 7 && value1 != 8) || (value2 != 0 && value2 != 3 && value2 != 4 && value2 != 7 && value2 != 8))
				{
					y_now = y2 * square_size;
					y_now -= height_frame;
					y_move = 0;
					on_the_ground = true;
				}
			}
		}
		else if (y_move < 0) // nhan vat nhay len
		{
			int value1 = map_data.map[y1][x1];
			int value2 = map_data.map[y1][x2];
			if (value1 == 9 || value2 == 9)
			{
				map_data.map[y1][x1] = 0;
				map_data.map[y1][x2] = 0;
				Money();
			}
			else if (value1 == 7 || value2 == 7)
			{
				comeback_time = 10;
			}
			else
			{
				if ((value1 != 0 && value1 != 3 && value1 != 4 && value1 != 5 && value1 != 7 && value1 != 8) || (value2 != 0 && value2 != 3 && value2 != 4 && value2 != 5 && value2 != 7 && value2 != 8))
				{
					y_now = (y1 + 1) * square_size;
					y_move = 0;
				}
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

void Player::Money()
{
	money_count++;
}
