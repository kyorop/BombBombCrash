#pragma once
class Timer
{
private:
	int count;
	bool reset;
	int startTime;
public:
	//ŒÄ‚Ño‚³‚ê‚Ä‚©‚çˆø”w’èƒ~ƒŠ•b‚ª‚½‚Á‚½‚çTRUE‚ğ•Ô‚·
	bool CountDown(int millisecond);
	Timer(void);
	~Timer(void);
	void TurnReset(void);
};

