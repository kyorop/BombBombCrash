#pragma once
class Timer
{
private:
	int count;
	bool reset;
	int startTime;
public:
	bool CountDown(int time);
	Timer(void);
	~Timer(void);
};

