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

void EnemyAI::CheckBombCAroundMyself(const Enemy &myself)
{
	int i_current = myself.GetY() / 32;
	int j_current = myself.GetX() / 32;

	for (int j = 0; j < GameConst::MAP_LINE; ++j)
	{
		if(MapState::GetInstance()->GetState(i_current, j, MAP) == 1 || MapState::GetInstance()->GetState(i_current, j, BLOCK) == 1)
			break;
		if(MapState::GetInstance()->GetState(i_current, j, BOMB) == 1)
		{

		}
	}

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
}


