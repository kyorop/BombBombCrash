#pragma once
#include "GameConstant.h"
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

class Enemy;
class Dijkstra;
class Search;
class EnemyAI
{
private:
	int i_safe;
	int j_safe;
	int rand;
	int hasCalked;
	int currentOrder;
	int x_next;
	int y_next;
	int x_center;
	int y_center;
	int isStop;
	int nowExploring;
	Dijkstra *dijkstra;
	Search *search;

	//長期目標ルート
	std::list<int> targetRoute;
	//短期危険回避ルート
	std::list<int> noDengerRoute;

	//目的地候補の格納
	std::vector<int> i_goal;
	std::vector<int> j_goal;

public:
	void Analyse(int i_current, int j_current, Enemy *myself);
	int GetAction(const Enemy &myself);
		
	EnemyAI();
	~EnemyAI(void);
};

