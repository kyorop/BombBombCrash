#pragma once
class Timer
{
private:
	int count;
	bool reset;
	int startTime;
public:
	//�Ăяo����Ă�������w��~���b����������TRUE��Ԃ�
	bool CountDown(int millisecond);
	Timer(void);
	~Timer(void);
	void TurnReset(void);
};

