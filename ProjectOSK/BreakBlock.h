#pragma once
#include "State.h"

namespace BombBombCrash
{
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
}




