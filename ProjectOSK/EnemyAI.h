#pragma once
#include "GameConstant.h"
////#include <vector>
#include <list>
////#include <queue>
////#include <stack>
////#include <vector>
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

class Enemy;
class Dijkstra;
class Search;
class Route;
class Target;
class Avoid;
class StopRoute;
class EnemyAI
{
private:
	enum procedure
	{
		END,
		TARGET,
		AVOID,
		STOPTHOUGHT,
	};
	 procedure nextState;
	 procedure currentState;
	 Route *route;
	int hasCalculated;
	int x_next;
	int y_next;

	//int nowExploring;
	Target *const target;
	Avoid *const avoid;
	StopRoute *const stop;
	Search *const search;
private:
	int CheckBombCAroundMyself(const Enemy &myself);
	int CheckDanager(const Enemy &myself);
	int CheckAbleToMove(const Enemy &myself);
public:
	void Analyse(int i_current, int j_current, const Enemy &myself);
	int GetAction(const Enemy &myself);
		
	EnemyAI();
	~EnemyAI(void);
};

