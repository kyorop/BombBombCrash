#pragma once
#include "State.h"


class BreakBlock
	:public State
{
private:
	void ChangeState();
public:
	BreakBlock(IStateChanger *stateMrg);
	~BreakBlock(void);

	void Analyse(const Enemy &myself);
};

