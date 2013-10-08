#pragma once
#include "GameConstant.h"
//#include <list>
#include <vector>
#include <queue>

class Search
{
//�e���\�b�h���p
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
	//�����Ɏw�肵���ꏊ�����ƂɖړI�n(�u���b�N�̐^��)�����肷��
	void SetGoalInitialized(const int i_from, const int j_from, std::vector<int> *i_goal, std::vector<int> *j_goal);

	//�����Ɏw�肵���ꏊ�����Ƃɓ�����ꏊ�����肷��
	void CheckAbleToAvoidFromBomb(const int i_from, const int j_from, int *i_safe, int *j_safe);

	//�����Ɏw�肵���ꏊ���甚���͈͂Ɋ������܂�Ȃ��悤�ɑ��̏ꏊ�ֈړ��ł��邩�`�F�b�N����
	//�ړ��ł���Ȃ�P��Ԃ��B�ړ��ł��Ȃ��Ȃ�O��Ԃ��B
	int CheckAbleToMoveInitialized(const int i_start, const int j_start, int *const i_safe, int *const j_safe);


	Search(void);
	~Search(void);
};

