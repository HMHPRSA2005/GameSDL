#pragma once

class Timer
{
private:
	int start_tick;
	int pause_tick;

	bool is_pause_;
	bool is_start_;
public:
	Timer();
	~Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	int get_tick();

	bool is_pause();
	bool is_start();
};