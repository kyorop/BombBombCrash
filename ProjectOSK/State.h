#pragma once
#include <list>
#include "Search.h"
#include "Dijkstra.h"
#include "Enemy.h"
#include "IStateChanger.h"

class State
{
protected:
	enum
		{
			END = -1,
			STOP,
			LEFT,
			RIGHT,
			UP,
			DOWN,
			BOMBSET,
			BOMBSETOFF,
		};
protected:
	IStateChanger*const stateMrg;
	std::list<int> routeList;
	Search *const search;
	Dijkstra *const dijkstra;
	int x_now;
	int y_now;
	int x_center;
	int y_center;
	int i_center;
	int j_center;
	int hasCalculated;
	int x_next;
	int y_next;
	int reset;
protected:
	//指定した対象が指定した半径にあり、かつそこへ行けるなら１を返す
	int CheckAroundMyself(int i_now, int j_now/*, int* i_to, int* j_to*/, int TRAGET, int radius);
	virtual void ChangeState() = 0;
public:
	State(IStateChanger *stateMrg);
	virtual ~State(void);
	virtual void Analyse(const Enemy &myself) = 0;
	virtual int GetRoute(const Enemy &myself);
};

