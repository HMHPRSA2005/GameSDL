#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
	x_move = 0;
	y_move = 0;
	is_move = false;
}

Bullet::~Bullet()
{
	Free();
}

void Bullet::HandleMove(const int& x_limit, const int& y_limit)
{
	if (bullet_direction == DIRECTION_RIGHT)
	{
		rect.x += x_move;
		if (rect.x > x_limit)
		{
			is_move = false;
		}
	}
	else if (bullet_direction == DIRECTION_LEFT)
	{
		rect.x -= x_move;
		if (rect.x < 0)
		{
			is_move = false;
		}
	}
}