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
		GETITEM,
	};
public:
	virtual ~IStateChanger(){};

	virtual void ChangeState(int nextState) = 0;
};