#pragma once
#include "GameConstant.h"
////#include <vector>
////#include <list>
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
class EnemyAI
{
private:
	//int i_safe;
	//int j_safe;
	//int rand;
	//int hasCalked;
	//int currentOrder;
	//int x_next;
	//int y_next;
	//int x_center;
	//int y_center;
	//int isStop;
	//Dijkstra *dijkstra;
	//Search *search;
	////長期目標ルート
	//std::list<int> targetRoute;
	////短期危険回避ルート
	//std::list<int> noDengerRoute;
	////目的地候補の格納
	//std::vector<int> i_goal;
	//std::vector<int> j_goal;

	int nowExploring;
	Target *const target;
	Avoid *const avoid;

	Route *route;
private:
	void CheckBombCAroundMyself(const Enemy &myself);
public:
	void Analyse(int i_current, int j_current, const Enemy &myself);
	int GetAction(const Enemy &myself);
		
	EnemyAI();
	~EnemyAI(void);
};

