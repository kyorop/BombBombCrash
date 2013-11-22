#include "Timer.h"
#include "Image.h"
#include "DxLib.h"

int Timer::number[10];

Timer::Timer(void)
	:count(0),
	reset(true),
	startTime(0),
	limitedTime(0)
{
	LoadDivGraph("zerotonine.png", 10, 10, 1, 16,32, number);
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
}void Timer::TurnReset(void)
{
	reset = true;
}


int Timer::GetLeftedTime()const
{
	if(reset == false)
		return limitedTime - (GetNowCount() - startTime);
	else
		return -1;
}


void Timer::DrawGraphicalTime(int x, int y)
{
	if(limitedTime > 0)
	{
		int leftedTime = limitedTime - (GetNowCount() - startTime);
		int minute = leftedTime / (60*1000);
		int second = ( leftedTime % (60*1000) ) / 1000;

		int minute_onesplace = minute;
		int second_tensplace = second/10;
		int second_onesplace = second - 10*second_tensplace;

		DrawGraph(x, y, Image::GetInstance()->number[minute_onesplace], true);
		DrawGraph(x+15, y, Image::GetInstance()->colon, true);
		DrawGraph(x+33, y, Image::GetInstance()->number[second_tensplace], true);
		DrawGraph(x+33+35, y, Image::GetInstance()->number[second_onesplace], true);
	}
}