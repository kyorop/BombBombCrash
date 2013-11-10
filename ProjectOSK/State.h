#pragma once
#include <list>
#include "Search.h"
#include "Dijkstra.h"
#include "Enemy.h"
#include "IStateChanger.h"


class Enemy;
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
	const Enemy& myself;
	int x_center;
	int y_center;
	int i_center;
	int j_center;
	int x_next;
	int y_next;
	int resetRoute;
	int currentAction;
	int resetCalc;
protected:
	//�w�肵���Ώۂ��w�肵�����a�ɂ���A�������֍s����Ȃ�P��Ԃ�
	int CheckAroundMyself(int i_now, int j_now/*, int* i_to, int* j_to*/, int TRAGET, int radius);
	virtual void ChangeState() = 0;
public:
	State(IStateChanger *stateMrg, const Enemy &myself);
	virtual ~State(void);
	virtual void Analyse() = 0;
	virtual int GetRoute();
};

