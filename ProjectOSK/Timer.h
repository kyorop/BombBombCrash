#pragma once
class Timer
{
private:
	int count;
	bool reset;
	int startTime;
public:
	//呼び出されてから引数指定ミリ秒がたったらTRUEを返す
	bool CountDown(int millisecond);
	Timer(void);
	~Timer(void);
	void TurnReset(void);
};

