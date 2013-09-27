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
	goal(0),
	visited()
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
	//一度通ったところにまた通らないように通過フラグを立てる
	visited[i][j] = 1;

	//目的地になるか調査
	if(BLOCK(i, -1, j, 0) || BLOCK(i, 1, j, 0) || BLOCK(i, 0, j, -1) || BLOCK(i, 0, j, 1))
	{
		i_goal.push_back(i);
		j_goal.push_back(j);
	}

	//通れるところに進む
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
		goal = 1;

	if( goal == 0 && visited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 )
	{
		muki = UP;
		SetRoute(i-1, j,i_goal, j_goal);
	}
	if( goal == 0 && visited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 ) 
	{
		muki = DOWN;
		SetRoute(i+1, j, i_goal, j_goal);
	}
	if( goal == 0 && visited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 )
	{
		muki = LEFT;
		SetRoute(i, j-1, i_goal, j_goal);
	}
	if( goal == 0 && visited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 ) 
	{
		muki = RIGHT;
		SetRoute(i, j+1, i_goal, j_goal);
	}

	if(goal == 0)
		route.pop_back();
}

int EnemyAI::Analyse(int i, int j)
{
		int n;

		Initialize();
		SetGoal(i, j);

		n = GetRand(i_goal.size() - 1);
		Initialize();
		SetRoute(i, j, i_goal[n], j_goal[n]);
}

int EnemyAI::GetAction(int next)
{
	if(next == 1)
		route.pop_front();
	
	if(route.empty() == 1)
		return -1;

	std::list<int>::iterator it = route.begin();
	return *it;
}

EnemyAI::~EnemyAI(void)
{
}
