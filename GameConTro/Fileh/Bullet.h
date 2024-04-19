#pragma once

#include "BaseObject.h"
#include "CommonFunction.h"

class Bullet : public BaseObject
{
private:
	int x_move;
	int y_move;
	bool is_move;
	unsigned int bullet_direction;

public:
	Bullet();
	~Bullet();

	enum BulletDirection
	{
		DIRECTION_RIGHT = 20,
		DIRECTION_LEFT = 21,
	};

	void set_x_move(const int& xMove) { x_move = xMove; }
	void set_y_move(const int& yMove) { y_move = yMove; }
	int get_x_move() const { return x_move; }
	int get_y_move() const { return y_move; }

	void set_is_move(const bool& isMove) { is_move = isMove; }
	bool get_is_move() const { return is_move; }

	void set_bullet_direction(const unsigned int& bulletDirection) { bullet_direction = bulletDirection; }
	int get_bullet_direction() const { return bullet_direction; }

	void HandleMove(const int& x_limit, const int& y_limit);
};
