#pragma once
#include "Dijkstra.h"
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include "GameConstant.h"
#include <vector>
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

class EnemyAI
{
private:
	
public:
	//共通利用
	//int visited[MAPSIZE_Y][MAPSIZE_X];
	int visited[GameConst::MAP_ROW][GameConst::MAP_LINE];
	int hasVisited[GameConst::MAP_ROW][GameConst::MAP_LINE];
	int success;
	//for SetRoute()
	//for CheckAbleToEscapeFromBomb()
	int checkedOtherRow;
	int checkedOtherLine;
	Dijkstra *dijkstra;
	//長期目標ルート
	std::list<int> targetRoute;
	//短期危険回避ルート
	std::list<int> noDengerRoute;
public:
	std::queue<int> que_i;
	std::queue<int> que_j;

	void Initialize();
	void SetGoal(const int i, const int j);
	//void SetRoute(const int i, const int j, const int goal_i, const int goal_j);
	int i_safe;
	int j_safe;
	//int CheckAbleToEscapeFromBomb(const int i, const int j);
	int CheckAbleToMove(const int i_now, const int j_now);
	void CheckAbleToEscapeFromBomb(const int i, const int j);
	int rand;
	void CheckBomb();
	void Analyse(int i_current, int j_current);
	std::vector<int> i_goal;
	std::vector<int> j_goal;
	std::vector<int> route;
	int GetAction(int next);
	EnemyAI(void);
	~EnemyAI(void);
};

