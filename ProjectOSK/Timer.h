#pragma once
class Timer
{
private:
	int count;
	bool reset;
	int startTime;
	int limitedTime;
	static int number[10];
public:
	//呼び出されてから引数指定ミリ秒がたったらTRUEを返す
	bool CountDown(int millisecond);
	Timer(void);
	~Timer(void);
	void TurnReset(void);
	int GetLeftedTime()const;
	void DrawGraphicalTime(int x, int y);
};

