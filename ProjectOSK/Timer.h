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
	//ŒÄ‚Ño‚³‚ê‚Ä‚©‚çˆø”w’èƒ~ƒŠ•b‚ª‚½‚Á‚½‚çTRUE‚ğ•Ô‚·
	bool CountDown(int millisecond);
	Timer(void);
	~Timer(void);
	void TurnReset(void);
	int GetLeftedTime()const;
	void DrawGraphicalTime(int x, int y);
};

