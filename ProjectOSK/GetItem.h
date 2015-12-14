#pragma once
#include "State.h"


namespace BombBombCrash
{
	class GetItem
		:public State
	{
	private:
		void ChangeState()override;
	public:
		GetItem(IStateChanger *stateMrg, const Enemy& myself);
		~GetItem();

		void Analyse()override;
	};       
}


