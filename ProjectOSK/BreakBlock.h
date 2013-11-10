#pragma once
#include "State.h"

class Enemy;
class BreakBlock
	:public State
{
private:
	void ChangeState();
public:
	BreakBlock(IStateChanger *stateMrg, const Enemy& myself);
	~BreakBlock();

	void Analyse();
};

