#pragma once
#include "GameConstant.h"
//#include <list>
#include <vector>
#include <queue>

class Search
{
//各メソッド共用
private:
	int hasVisited[GameConst::MAP_ROW][GameConst::MAP_LINE];

//for SetGoal method
private:
	//std::vector<int> i_goal;
	//std::vector<int> j_goal;

//for CheckAbleToBombAvoid method
private:
	std::queue<int> que_i;
	std::queue<int> que_j;
	//int i_safe;
	//int j_safe;

//for CheckBomb method
private:
	int checkedOtherRow;
	int checkedOtherLine;
	int success;

private:
	//void Initialize();

	void SetGoal(const int i_start, const int j_start, std::vector<int> *i_goal, std::vector<int> *j_goal);
	int CheckAbleToMove(const int i_start, const int j_start, int *const i_safe, int *const j_safe);

public:
	//引数に指定した場所をもとに目的地(ブロックの真横)を決定する
	void SetGoalInitialized(const int i_from, const int j_from, std::vector<int> *i_goal, std::vector<int> *j_goal);

	//引数に指定した場所をもとに逃げる場所を決定する
	void CheckAbleToAvoidFromBomb(const int i_from, const int j_from, int *i_safe, int *j_safe);

	//引数に指定した場所から爆風範囲に巻き込まれないように他の場所へ移動できるかチェックする
	//移動できるなら１を返す。移動できないなら０を返す。
	int CheckAbleToMoveInitialized(const int i_start, const int j_start, int *const i_safe, int *const j_safe);


	Search(void);
	~Search(void);
};

