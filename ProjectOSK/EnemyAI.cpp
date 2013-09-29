#include "EnemyAI.h"
#include "MapState.h"
#include "DxLib.h"
enum
{
	STOP,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	BOMBSET,
	BOMBSETOFF,
};

#define BLOCK(i, p, j, q) MapState::GetInstance()->GetState(i+p, j+q, BLOCK)
#define MAP(i, p, j, q) MapState::GetInstance()->GetState(i+p, j+q, MAP)

EnemyAI::EnemyAI(void):
	success(0),
	muki(STOP),
	visited(),
	checkedOtherRow(0),
	checkedOtherLine(0),
	i_safe(),
	j_safe()
{

	for (int i = 0; i < MapState::row; i++)
	{
		for (int j = 0; j < MapState::line; j++)
		{
			this->visited[i][j] = 0;
		}
	}

}

void EnemyAI::Initialize()
{
	for (int i = 0; i < MapState::row; i++)
	{
		for (int j = 0; j < MapState::line; j++)
		{
			this->visited[i][j] = 0;
		}
	}
	
}

void EnemyAI::SetGoal(const int i, const int j)
{
	//��x�ʂ����Ƃ���ɂ܂��ʂ�Ȃ��悤�ɒʉ߃t���O�𗧂Ă�
	visited[i][j] = 1;

	//�ړI�n�ɂȂ邩����
	if(BLOCK(i, 0, j, 0) || BLOCK(i, -1, j, 0) || BLOCK(i, 1, j, 0) || BLOCK(i, 0, j, -1) || BLOCK(i, 0, j, 1))
	{
		i_goal.push_back(i);
		j_goal.push_back(j);
	}

	//�ʂ��Ƃ���ɐi��
	if( visited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 ) SetGoal(i-1, j);
	if( visited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 ) SetGoal(i+1, j);
	if( visited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 ) SetGoal(i, j-1);
	if( visited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 ) SetGoal(i, j+1);
}

void EnemyAI::SetRoute(const int i, const int j, const int i_goal, const int j_goal)
{
	visited[i][j] = 1;
	
	if(muki != STOP)
		route.push_back(muki);

	if(i == i_goal && j == j_goal)
	{
		success = 1;
		//route.push_back(-1);
	}

	if( success == 0 && visited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 )
	{
		muki = UP;
		SetRoute(i-1, j,i_goal, j_goal);
	}
	if( success == 0 && visited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 ) 
	{
		muki = DOWN;
		SetRoute(i+1, j, i_goal, j_goal);
	}
	if( success == 0 && visited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 )
	{
		muki = LEFT;
		SetRoute(i, j-1, i_goal, j_goal);
	}
	if( success == 0 && visited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 ) 
	{
		muki = RIGHT;
		SetRoute(i, j+1, i_goal, j_goal);
	}

	if(success == 0)
		route.pop_back();
}

int EnemyAI::CheckAbleToEscapeFromBomb(const int i, const int j)
{
	visited[i][j] = 1;
	
	if( checkedOtherRow == 1 && checkedOtherLine == 1 )
	{
		i_safe = i;
		j_safe = j;
		success = 1;
	}

	//�ʂ��Ƃ���ɐi��
	if(success == 0 && visited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 )
	{
		checkedOtherRow = 1;
		CheckAbleToEscapeFromBomb(i-1, j);
	}
	if( success == 0 && visited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 )
	{
		checkedOtherRow = 1;
		CheckAbleToEscapeFromBomb(i+1, j);
	}
	if( success == 0 && visited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 )
	{
		checkedOtherLine = 1;
		CheckAbleToEscapeFromBomb(i, j-1);
	}
	if( success == 0 && visited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 )
	{
		checkedOtherLine = 1;
		CheckAbleToEscapeFromBomb(i, j+1);
	}

	//�ċA�I�ɌĂ΂ꂽ�֐����I��邱�Ƃ͂܂�T���̎����߂����Ƃ��Ӗ�����
	checkedOtherRow = 0;
	checkedOtherLine = 0;

	return success;
}

void CheckBomb()
{

}

void EnemyAI::Analyse(int i_current, int j_current)
{
	int n = 0;

	//�j�󂷂�ǂ̌���
	i_goal.clear();
	j_goal.clear();
	Initialize();
	SetGoal(i_current, j_current);
	
	//���߂�ꏊ���{����u���Ă����ꏊ�����ׂ�
	n = GetRand(i_goal.size() - 1);
	Initialize();
	while(CheckAbleToEscapeFromBomb(i_goal[n], j_goal[n]) == 0)
	{
		Initialize();
		int checkedOtherRow = 0;
		int checkedOtherLine = 0;
		int i_safe = 0;
		int j_safe = 0;
	}

	//�j�󂷂�ǂ܂ł̃��[�g�Z�b�g
	route.clear();
	success = 0;
	muki = STOP;
	Initialize();
	SetRoute(i_current, j_current, i_goal[n], j_goal[n]);
	
	//�j�󂷂�ǂ���{�������n�܂ł̃��[�g�Z�b�g
	route.push_back(BOMBSET);
	route.push_back(BOMBSETOFF);
	Initialize();
	success = 0;
	muki = STOP;
	SetRoute(i_goal[n], j_goal[n], i_safe, j_safe);
	route.push_back(-1);
}

int EnemyAI::GetAction(int num)
{
	//if(next == 1)
	//	route.pop_front();
	//if(route.empty() == 1)
	//	return -1;
	//std::list<int>::iterator it = route.begin();
	//return *it;

	return route[num];
}

EnemyAI::~EnemyAI(void)
{
}
