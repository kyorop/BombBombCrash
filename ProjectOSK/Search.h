#pragma once
#include "GameConstant.h"
#include <list>
#include <vector>
#include <queue>
																													
class Search
{
//�e���\�b�h���p
private:
	int hasVisited[GameConst::MAP_ROW][GameConst::MAP_LINE];
	int count;
	int failed;
//for CheckAbleToBombAvoid method
private:
	std::queue<int> que_i;
	std::queue<int> que_j;
//for CheckBomb method
private:
	int checkedOtherRow;
	int checkedOtherLine;
	int success;

private:
	void SetGoal(const int i_start, const int j_start, std::vector<int> *i_goal, std::vector<int> *j_goal);
	int CheckAbleToMove(const int i_start, const int j_start, int *const i_safe, int *const j_safe);
	int OnlyCheckAbleToMove(int i_now, int j_now, int i_end, int j_end);
	void SetEscapeRouteToStop(int i_now, int j_now, std::list<int> escapeRoute);

public:
	//�����Ɏw�肵���ꏊ�����ƂɖړI�n(�u���b�N�̐^��)�����肷��
	void SetGoalInitialized(const int i_from, const int j_from, std::vector<int> *i_goal, std::vector<int> *j_goal);
	
	//�����Ɏw�肵���ꏊ�����Ƃɓ�����ꏊ�����肷��
	//void CheckAbleToAvoidFromBomb(const int i_from, const int j_from, int *i_safe, int *j_safe);
	
	//�����Ɏw�肵���ꏊ���甚���͈͂Ɋ������܂�Ȃ��悤�ɑ��̏ꏊ�ֈړ��ł��邩�`�F�b�N����
	//�ړ��ł���Ȃ�P��Ԃ��B�ړ��ł��Ȃ��Ȃ�O��Ԃ��B
	int CheckAbleToMoveInitialized(const int i_start, const int j_start, int *const i_safe, int *const j_safe);
	
	//�����͈͂ɓ����Ă��鎞�ɂ�������̍ŒZ�E�o���[�g��񋟂���
	void SetEscapeRouteWhenInDanger(int i, int j, std::list<int> escapeRoute);

	//��Ԃɂ��邩���ׂ�B
	//����Ȃ�P��Ԃ��B���Ȃ��Ȃ�O��Ԃ��B
	int CheckInClosedInterval(int i_now, int j_now);

	Search(void);
	~Search(void);
};

