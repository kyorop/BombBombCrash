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
	//�Ăяo����Ă�������w��~���b����������TRUE��Ԃ�
	bool CountDown(int millisecond);
	Timer(void);
	~Timer(void);
	void TurnReset(void);
	int GetLeftedTime()const;
	void DrawGraphicalTime(int x, int y);
};

