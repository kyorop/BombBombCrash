#include "Timer.h"

using namespace BombBombCrash;

Timer::Timer(void)
	:count(0),
	reset(true),
	startTime(0),
	limitedTime(0)
{
}


Timer::~Timer(void)
{
}


bool Timer::CountDownRealTime(int time)
{
	limitedTime = time;
	if(this->reset == true)
	{
		startTime = GetNowCount();
		reset = false;
	}

	if(GetNowCount() - startTime < time)
		return false;
	else
	{
		reset = true;
		return true;
	}
}


bool Timer::CountDownFrame(int time)
{
	if(reset == true)
	{
		count = 0;
		reset = false;
	}
	if(count < time / frameTime)
	{
		++count;
		return false;
	}
	else
	{
		reset = true;
		return true;
	}
}


void Timer::TurnReset(void)
{
	reset = true;
}


int Timer::GetLeftedRealTime()const
{
	if(reset == false)
		return limitedTime - (GetNowCount() - startTime);
	else
		return -1;
}
