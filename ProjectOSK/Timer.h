#pragma once
class Timer
{
private:
	int count;
	bool reset;
	int startTime;
public:
	bool CountDown();
	Timer(void);
	~Timer(void);
};

