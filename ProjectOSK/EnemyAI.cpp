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
	nowExploring(0),
	x_next(),
	y_next()
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
		//目的地(壊す壁)の決定
		i_goal.clear();
		j_goal.clear();
		search->SetGoalInitialized(i_current, j_current, &i_goal, &j_goal);
		
		//目的地までのルートセット
		n = GetRand(i_goal.size() - 1);
		rand = n;
		dijkstra->SearchShortestPath(i_current, j_current, i_goal[n], j_goal[n], &targetRoute);
		
		//破壊する壁からボム逃げ地までのルートセット
		targetRoute.push_back(BOMBSET);
		targetRoute.push_back(BOMBSETOFF);
		//->SearchShortestPath(i_goal[n], j_goal[n], i_safe, j_safe, &targetRoute);

		//安全地の座標決定
		search->CheckAbleToEscapeFromBomb(i_goal[n], j_goal[n], &i_safe, &j_safe);

		//安全地までのルートセット
		dijkstra->SearchShortestPath(i_goal[n], j_goal[n], i_safe, j_safe, &targetRoute);
		//targetRoute.push_back(STOP);
		nowExploring = 1;
	}
	
	//if(search->CheckAbleToMoveInitialized(i_safe, j_safe) == 0 )
	//{
	//	targetRoute.push_front(STOP);
	//	//isStop = 1;
	//}
	//if(search->CheckAbleToMoveInitialized(i_safe, j_safe) == 1)
	//{
	//	targetRoute.pop_back();
	//	//myself->CancelStop();
	//	//isStop = 0;
	//}

}

int EnemyAI::GetAction(const Enemy &myself)
{
	//int x_center;
	//int y_center;
	int i_current;		//呼び出し時にいたマスの成分
	int j_current;

	if(hasCalked == 0)
	{
		x_center = (myself.GetX() + myself.GetX()+32) / 2;
		y_center = (myself.GetY() + myself.GetY()+32) / 2;
		
		i_current = y_center / 32;
		j_current = x_center / 32;

		hasCalked  = 1;
	
		switch( targetRoute.front() )
		{
			case STOP:
				break;
			case UP:
				x_next = (j_current + 0) * 32;
				y_next = (i_current - 1) * 32;
				break;
			case DOWN:
				x_next = (j_current + 0) * 32;
				y_next = (i_current + 1) * 32;
				break;
			case LEFT:
				x_next = (j_current - 1) * 32;
				y_next = (i_current + 0) * 32;
				break;
			case RIGHT:
				x_next = (j_current + 1) * 32;
				y_next = (i_current + 0) * 32;
				break;
			case BOMBSET:
				//targetRoute.pop_front();
				break;
			case BOMBSETOFF:
				//targetRoute.pop_front();
				break;
			case -1:
				//targetRoute.pop_front();
				break;
		}
	}//end of if block

	//if(isStop == 0 && targetRoute.front() != STOP)
	//{
	//	targetRoute.pop_front();
	//}

	if(myself.GetX() == x_next && myself.GetY() == y_next)
	{
		targetRoute.pop_front();
		hasCalked = 0;
		
		if(targetRoute.empty() == 1)
		{
			nowExploring = 0;
			return END;
		}
	}

	return targetRoute.front();

}


