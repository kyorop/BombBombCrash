#pragma once

class IStateChanger
{
public:
	enum
	{
		NOCHAGE,
		ATTACK,
		ITEM,
		AVOID,
		BREAKBLOCK,
	};
public:
	virtual ~IStateChanger(){};

	virtual void ChangeState(int nextState) = 0;
};