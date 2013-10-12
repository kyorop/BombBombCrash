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
	int hasCalculated;
	int x_next;
	int y_next;

	int nowExploring;
	Target *const target;
	Avoid *const avoid;
	StopRoute *const stop;

	Route *route;
	Search *search;
private:
	int CheckBombCAroundMyself(const Enemy &myself);
	void CalculateNextPosition(const Enemy &myself ,int nextDirection);
	int CheckDanager(const Enemy &myself);
	int CheckAbleToMove(const Enemy &myself);
public:
	void Analyse(int i_current, int j_current, const Enemy &myself);
	int GetAction(const Enemy &myself);
		
	EnemyAI();
	~EnemyAI(void);
};

