#include "EnemyAI.h"
#include "MapState.h"
#include "Enemy.h"
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

EnemyAI::EnemyAI():
	hasCalked(0),
	rand(-1),
	success(0),
	hasVisited(),
	visited(),
	checkedOtherRow(0),
	checkedOtherLine(0),
	i_safe(-1),
	j_safe(-1),
	dijkstra(new Dijkstra),
	targetRoute(),
	noDengerRoute(),
	que_i(),
	que_j()
{
	for (int i = 0; i < MapState::row; i++)
	{
		for (int j = 0; j < MapState::line; j++)
		{
			this->visited[i][j] = 0;
			hasVisited[i][j] = 0;
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
			hasVisited[i][j] = 0;
		}
	}
	while(que_i.empty() == 0)
	{
		que_i.pop();
	}

	while(que_j.empty() == 0)
	{
		que_j.pop();
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

void EnemyAI::CheckAbleToEscapeFromBomb(const int i_start, const int j_start)
{
	int size;
	int i;
	int j;

	//初期位置をキューに追加
	que_i.push(i_start);
	que_j.push(j_start);
	
	while(i_safe == -1 || j_safe == -1)
	{
		size = que_i.size();
		for(int n=0; n<size; ++n)
		{
			i = que_i.front();
			j = que_j.front();

			//逃げれるかチェック
			if( i != i_start && j != j_start)
			{
				i_safe = i;
				j_safe = j;
				break;
			}

			//逃げれないならキューの更新
			if(hasVisited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 )
			{
				hasVisited[i-1][j] = 1;
				que_i.push(i-1);
				que_j.push(j);
			}
			if( hasVisited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 )
			{
				hasVisited[i+1][j] = 1;
				que_i.push(i+1);
				que_j.push(j);
			}
			if( hasVisited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 )
			{
				hasVisited[i][j-1] = 1;
				que_i.push(i);
				que_j.push(j-1);
			}
			if( hasVisited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 )
			{
				hasVisited[i][j+1] = 1;
				que_i.push(i);
				que_j.push(j+1);
			}

			que_i.pop();
			que_j.pop();
		}
	}

}

//int EnemyAI::CheckAbleToMove(const int i, const int j)
//{
//	visited[i][j] = 1;
//	
//	if( checkedOtherRow == 1 && checkedOtherLine == 1 )
//	{
//		success = 1;
//	}
//
//	//通れるところに進む
//	if(success == 0 && visited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 )
//	{
//		checkedOtherRow = 1;
//		CheckAbleToEscapeFromBomb(i-1, j);
//	}
//	if( success == 0 && visited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 )
//	{
//		checkedOtherRow = 1;
//		CheckAbleToEscapeFromBomb(i+1, j);
//	}
//	if( success == 0 && visited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 )
//	{
//		checkedOtherLine = 1;
//		CheckAbleToEscapeFromBomb(i, j-1);
//	}
//	if( success == 0 && visited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 )
//	{
//		checkedOtherLine = 1;
//		CheckAbleToEscapeFromBomb(i, j+1);
//	}
//
//	checkedOtherRow = 0;
//	checkedOtherLine = 0;
//
//	return success;
//}

int EnemyAI::CheckBomb(const int i, const int j)
{
	hasVisited[i][j] = 1;
	
	if( checkedOtherRow == 1 && checkedOtherLine == 1 )
	{
		success = 1;
	}

	//通れるところに進む
	if(success == 0 && hasVisited[i-1][j] == 0 && MAP(i, -1, j, 0) == 0 && BLOCK(i, -1, j, 0) == 0 && MapState::GetInstance()->GetDangerState(i-1, j) == NODENGER)
	{
		checkedOtherRow = 1;
		CheckAbleToEscapeFromBomb(i-1, j);
	}
	if( success == 0 && hasVisited[i+1][j] == 0 && MAP(i, 1, j, 0) == 0 && BLOCK(i, 1, j, 0) == 0 && MapState::GetInstance()->GetDangerState(i+1, j) == NODENGER)
	{
		checkedOtherRow = 1;
		CheckAbleToEscapeFromBomb(i+1, j);
	}
	if( success == 0 && hasVisited[i][j-1] == 0 && MAP(i, 0, j, -1) == 0 && BLOCK(i, 0, j, -1) == 0 && MapState::GetInstance()->GetDangerState(i, j-1) == NODENGER)
	{
		checkedOtherLine = 1;
		CheckAbleToEscapeFromBomb(i, j-1);
	}
	if( success == 0 && hasVisited[i][j+1] == 0 && MAP(i, 0, j, 1) == 0 && BLOCK(i, 0, j, 1) == 0 && MapState::GetInstance()->GetDangerState(i, j+1) == NODENGER)
	{
		checkedOtherLine = 1;
		CheckAbleToEscapeFromBomb(i, j+1);
	}

	checkedOtherRow = 0;
	checkedOtherLine = 0;

	return success;
}

void EnemyAI::Analyse(int i_current, int j_current, Enemy *myself)
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
	//success = 0;
	//checkedOtherRow = 0;
	//checkedOtherLine = 0;
	i_safe = -1;
	j_safe = -1;
	rand = n;
	CheckAbleToEscapeFromBomb(i_goal[n], j_goal[n]);
	/*while(CheckAbleToEscapeFromBomb(i_goal[n], j_goal[n]) == 0)
	{
		rand = GetRand(i_goal.size() - 1);
	}*/
	/*while(1)
	{
		if(CheckAbleToEscapeFromBomb(i_goal[n], j_goal[n]) == 1)
		{
			
			break;
		}
		n = GetRand(i_goal.size() - 1);

	}*/

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
	
	Initialize();
	success = 0;
	checkedOtherRow = 0;
	checkedOtherLine = 0;
	if(CheckBomb(i_current, j_current) == 0 )
	{
		dijkstra->SetBombAction(STOP);
	}

	Initialize();
	success = 0;
	checkedOtherRow = 0;
	checkedOtherLine = 0;
	if(CheckBomb(i_current, j_current) == 1 )
	{
		myself->CancelStop();
	}
}

int EnemyAI::GetAction(const Enemy &myself)
{
	int x_center;
	int y_center;
	int i;
	int j;

	if(hasCalked == 0)
	{
		x_center = (myself.GetX() + myself.GetRX()) / 2;
		y_center = (myself.GetY() + myself.GetDY()) / 2;
		
		i = y_center / 32;
		j = x_center / 32;
		
		x_next = j * 32;
		y_next = i * 32;
		hasCalked  = 1;
	
		switch( targetRoute.front() )
		{
			case STOP:
				break;
			case UP:
				x_next = (x_center/32 + 0) * 32;
				y_next = (y_center/32 - 1) * 32;
				break;
			case DOWN:
				x_next = (x_center/32 + 0) * 32;
				y_next = (y_center/32 + 1) * 32;
				break;
			case LEFT:
				x_next = (x_center/32 - 1) * 32;
				y_next = (y_center/32 + 0) * 32;
				break;
			case RIGHT:
				x_next = (x_center/32 + 1) * 32;
				y_next = (y_center/32 + 0) * 32;
				break;
			case BOMBSET:
				break;
			case BOMBSETOFF:
				break;
			case -1:
				break;
		}

	}//end of if block

	if(myself.GetX() == x_next && myself.GetY() == y_next)
	{

	}

	//return dijkstra->GetRoute(num);
}

EnemyAI::~EnemyAI(void)
{
	delete dijkstra;
}
