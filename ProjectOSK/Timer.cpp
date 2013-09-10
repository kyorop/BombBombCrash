#include "Timer.h"
#include "DxLib.h"

Timer::Timer(void)
{
	this->reset = true;
	this->startTime = 0;
	this->count = 0;
}

bool Timer::CountDown(int time)
{
	if(this->reset == true)
	{
		this->startTime = GetNowCount();
		this->reset = false;
	}
	if(GetNowCount() - this->startTime < time)
		return false;
	else
	{
		this->reset = true;
		return true;
	}
}

Timer::~Timer(void)
{
}


void Timer::TurnReset(void)
{
	this->reset = true;
}
