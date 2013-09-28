#pragma once
#include <vector>
#include <list>
#include <queue>
#include <stack>
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

class EnemyAI
{
private:
	//‹¤’Ê—˜—p
	int visited[MAPSIZE_Y][MAPSIZE_X];
	int success;
	//for SetRoute()
	int muki;
	//for CheckAbleToEscapeFromBomb()
	int checkedOtherRow;
	int checkedOtherLine;
	int i_safe;
	int j_safe;
private:
	void Initialize();
	void SetGoal(const int i, const int j);
	void SetRoute(const int i, const int j, const int goal_i, const int goal_j);
public:
	int CheckAbleToEscapeFromBomb(const int i, const int j);
	void CheckBomb();
	void Analyse(int i, int j);
	std::vector<int> i_goal, j_goal;
	std::vector<int> route;
	int GetAction(int next);
	EnemyAI(void);
	~EnemyAI(void);
};

