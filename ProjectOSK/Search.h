#pragma once
#include "GameConstant.h"
#include <vector>
#include <queue>

class Search
{
//各メソッド共用
private:
	int hasVisited[GameConst::MAP_ROW][GameConst::MAP_LINE];

//for SetGoal
private:
	std::vector<int> i_goal;
	std::vector<int> j_goal;

//for CheckAbleToBombEscape
private:
	std::queue<int> que_i;
	std::queue<int> que_j;
	int i_safe;
	int j_safe;

//for CheckBomb
private:
	int checkedOtherRow;
	int checkedOtherLine;
	int success;

private:
	void Initialize();
public:
	void SetGoal(const int i_start, const int j_start);
	void CheckAbleToEscapeFromBomb(const int i_start, const int j_start);
	int CheckBomb(const int i_start, const int j_start);


	Search(void);
	~Search(void);
};

