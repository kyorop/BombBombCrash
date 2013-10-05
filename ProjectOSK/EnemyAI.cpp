#include "EnemyAI.h"
#include "MapState.h"
#include "Enemy.h"
#include "Dijkstra.h"
#include "Search.h"
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
	i_safe(-1),
	j_safe(-1),
	dijkstra(new Dijkstra),
	search(new Search),
	targetRoute(),
	noDengerRoute(),
	isStop(0),
	nowExploring(0)
{
}

EnemyAI::~EnemyAI(void)
{
	delete dijkstra;
	delete search;
}

void EnemyAI::Analyse(int i_current, int j_current, Enemy *myself)
{
	int n = 0;
	if(nowExploring == 0 )
	{
		//破壊する壁の決定
		i_goal.clear();
		j_goal.clear();
		search->SetGoalInitialized(i_current, j_current, &i_goal, &j_goal);
	
		//決める場所がボムを置いていい場所か調べる
		n = GetRand(i_goal.size() - 1);
		rand = n;
		search->CheckAbleToEscapeFromBomb(i_goal[n], j_goal[n], &i_safe, &j_safe);

		//破壊する壁までのルートセット
		dijkstra->SearchShortestPath(i_current, j_current, i_goal[n], j_goal[n], &targetRoute);
	
		//破壊する壁からボム逃げ地までのルートセット
		targetRoute.push_back(BOMBSET);
		targetRoute.push_back(BOMBSETOFF);
		dijkstra->SearchShortestPath(i_goal[n], j_goal[n], i_safe, j_safe, &targetRoute);
	}

	if(search->CheckAbleToMoveInitialized(i_current, j_current) == 0 )
	{
		//targetRoute.push_back(STOP);
		isStop = 1;
	}
	else
	{
		//myself->CancelStop();
		isStop = 0;
	}

}

int EnemyAI::GetAction(const Enemy &myself)
{
	int x_center;
	int y_center;
	int i;		//呼び出し時にいたマスの成分
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

	if(myself.GetX() == x_next && myself.GetY() == y_next && isStop == 0)
	{
		targetRoute.pop_front();
		hasCalked = 0;
	}

}


