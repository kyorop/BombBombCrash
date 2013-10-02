#include "EnemyAI.h"
#include "MapState.h"
#include "DxLib.h"
enum
{
	END = -1,
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
	rand(-1),
	success(0),
	visited(),
	checkedOtherRow(0),
	checkedOtherLine(0),
	i_safe(),
	j_safe(),
	dijkstra(new Dijkstra),
	targetRoute(),
	noDengerRoute()
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
	if(BLOCK(i, 0, j, 0) || BLOCK(i, -1, j, 0) || BLOCK(i, 1, j, 0) || BLOCK(i, 0, j, -1) || BLOCK(i, 0, j, 1))
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


int EnemyAI::CheckAbleToEscapeFromBomb(const int i, const int j)
{
	visited[i][j] = 1;
	
	if( checkedOtherRow == 1 && checkedOtherLine == 1 )
	{
		i_safe = i;
		j_safe = j;
		success = 1;
	}

	//通れるところに進む
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

	//再帰的に呼ばれた関数が終わることはつまり探索の手を一つ戻すことを意味する
	checkedOtherRow = 0;
	checkedOtherLine = 0;

	return success;
}

int EnemyAI::CheckAbleToMove(const int i_now, const int j_now)
{
	visited[i][j] = 1;
	
	if( checkedOtherRow == 1 && checkedOtherLine == 1 )
	{
		success = 1;
	}

	//通れるところに進む
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

	//破壊する壁の決定
	i_goal.clear();
	j_goal.clear();
	Initialize();
	SetGoal(i_current, j_current);
	
	//決める場所がボムを置いていい場所か調べる
	n = GetRand(i_goal.size() - 1);
	Initialize();
	success = 0;
	checkedOtherRow = 0;
	checkedOtherLine = 0;
	i_safe = 0;
	j_safe = 0;
	/*while(CheckAbleToEscapeFromBomb(i_goal[n], j_goal[n]) == 0)
	{
		rand = GetRand(i_goal.size() - 1);
	}*/
	while(1)
	{
		if(CheckAbleToEscapeFromBomb(i_goal[n], j_goal[n]) == 1)
		{
			rand = n;
			break;
		}
		n = GetRand(i_goal.size() - 1);

	}

	//破壊する壁までのルートセット
	route.clear();
	/*success = 0;
	muki = STOP;
	Initialize();
	SetRoute(i_current, j_current, i_goal[n], j_goal[n]);*/
	dijkstra->ResetRoute();
	dijkstra->SearchShortestPath(i_current, j_current, i_goal[n], j_goal[n]);
	
	//破壊する壁からボム逃げ地までのルートセット
	/*route.push_back(BOMBSET);
	route.push_back(BOMBSETOFF);
	Initialize();
	success = 0;
	muki = STOP;
	SetRoute(i_goal[n], j_goal[n], i_safe, j_safe);*/
	dijkstra->SetBombAction(BOMBSET);
	dijkstra->SetBombAction(BOMBSETOFF);
	dijkstra->SearchShortestPath(i_goal[n], j_goal[n], i_safe, j_safe);

	//アクションリストの最後を表す-1
	//route.push_back(-1);
}

int EnemyAI::GetAction(int num)
{
	//if(next == 1)
	//	route.pop_front();
	//if(route.empty() == 1)
	//	return -1;
	//std::list<int>::iterator it = route.begin();
	//return *it;

	//return route[num];

	return dijkstra->GetRoute(num);
}

EnemyAI::~EnemyAI(void)
{
	delete dijkstra;
}
