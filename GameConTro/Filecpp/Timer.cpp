
#include "stdafx.h"
#include "Timer.h"
#include "CommonFunction.h"

Timer::Timer()
{
	start_tick = 0;
	pause_tick = 0;
	is_pause_ = false;
	is_start_ = false;
}

Timer::~Timer()
{
	
}

void Timer::start()
{
	is_start_ = true;
	is_pause_ = false;
	start_tick = SDL_GetTicks();
}

void Timer::stop()
{
	is_pause_ = false;
	is_start_ = false;
}

void Timer::pause()
{
	if (is_start_ == true && is_pause_ == false)
	{
		is_pause_ = true;
		pause_tick = SDL_GetTicks() - start_tick;
	}
}

void Timer::unpause()
{
	if (is_pause_ == true)
	{
		is_pause_ = false;
		start_tick = SDL_GetTicks() - pause_tick;
		pause_tick = 0;
	}
}

int Timer::get_tick()
{
	if (is_start_ == true)
	{
		if (is_pause_ == true)
		{
			return pause_tick;
		}
		else
		{
			return SDL_GetTicks() - start_tick;
		}
	}
	return 0;
}

bool Timer::is_start()
{
	return is_start_;
}

bool Timer::is_pause()
{
	return is_pause_;
}