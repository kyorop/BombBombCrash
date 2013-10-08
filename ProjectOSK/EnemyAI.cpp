#include "EnemyAI.h"
#include "MapState.h"
#include "Enemy.h"
#include "Dijkstra.h"
#include "Search.h"
#include "Route.h"
#include "Target.h"
#include "Avoid.h"
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
	//hasCalked(0),
	//rand(-1),
	//i_safe(-1),
	//j_safe(-1),
	//dijkstra(new Dijkstra),
	//search(new Search),
	targetRoute(),
	//noDengerRoute(),
	//isStop(0),
	//x_next(),
	//y_next(),
	hasCalculated(0),
	nowExploring(0),
	target(new Target),
	avoid(new Avoid),
	route(target)
{
}

EnemyAI::~EnemyAI(void)
{
	//delete dijkstra;
	//delete search;
	delete target;
	delete avoid;
}

int EnemyAI::CheckBombCAroundMyself(const Enemy &myself)
{
	int i_current = myself.GetY() / 32;
	int j_current = myself.GetX() / 32;

	for (int j = 0; j < GameConst::MAP_LINE; ++j)
	{
		if(MapState::GetInstance()->GetState(i_current, j, MAP) == 1 || MapState::GetInstance()->GetState(i_current, j, BLOCK) == 1)
			continue;
		if(MapState::GetInstance()->GetState(i_current, j, BOMB) == 1)
		{
			if(route != target)
			{
				route = avoid;
				return 1;
			}
		}
	}

	for (int i = 0; i < GameConst::MAP_ROW; ++i)
	{
		if(MapState::GetInstance()->GetState(i, j_current, MAP) == 1 || MapState::GetInstance()->GetState(i, j_current, BLOCK) == 1)
			continue;
		if(MapState::GetInstance()->GetState(i, j_current, BOMB) == 1)
		{
			if(route != target)
			{
				route = avoid;
				//break;
				return 1;
			}
		}
	}

	return 0;
}

void EnemyAI::Analyse(int i_current, int j_current, const Enemy &myself)
{
	//int n = 0;
	//if(nowExploring == 0 )
	//{
	//	//目的地(壊す壁)の決定
	//	i_goal.clear();
	//	j_goal.clear();
	//	search->SetGoalInitialized(i_current, j_current, &i_goal, &j_goal);
	//	
	//	//目的地までのルートセット
	//	n = GetRand(i_goal.size() - 1);
	//	rand = n;
	//	dijkstra->SearchShortestPath(i_current, j_current, i_goal[n], j_goal[n], &targetRoute);
	//	
	//	//破壊する壁からボム逃げ地までのルートセット
	//	targetRoute.push_back(BOMBSET);
	//	targetRoute.push_back(BOMBSETOFF);
	//	//->SearchShortestPath(i_goal[n], j_goal[n], i_safe, j_safe, &targetRoute);

	//	//安全地の座標決定
	//	search->CheckAbleToAvoidFromBomb(i_goal[n], j_goal[n], &i_safe, &j_safe);

	//	//安全地までのルートセット
	//	dijkstra->SearchShortestPath(i_goal[n], j_goal[n], i_safe, j_safe, &targetRoute);
	//	//targetRoute.push_back(STOP);
	//	nowExploring = 1;
	//}
	//
	////if(search->CheckAbleToMoveInitialized(i_safe, j_safe) == 0 )
	////{
	////	targetRoute.push_front(STOP);
	////	//isStop = 1;
	////}
	////if(search->CheckAbleToMoveInitialized(i_safe, j_safe) == 1)
	////{
	////	targetRoute.pop_back();
	////	//myself->CancelStop();
	////	//isStop = 0;
	////}

	//if(myself.GetX() % 32 == 0 && myself.GetY() % 32 == 0)
	//{
	//	if(CheckBombCAroundMyself(myself) == 1) 
	//		nowExploring = 0;
	//}

	if(nowExploring == 0)
	{
		targetRoute.clear();
		if(myself.GetX() % 32 == 0 && myself.GetY() % 32 == 0)
		{
			route->DecideGoal(myself);
			route->SetRoute(myself);
		}
		else
			targetRoute.push_back(STOP);
		nowExploring = 1;
	}
}

void EnemyAI::CalculateNextPosition(const Enemy &myself, int nextDirection)
{
	//if(hasCalculated == 0)	//一度計算したら、一マス移動が終わるまで再計算しない
	//{
		int x_center, y_center;
		int i_current, j_current;		//呼び出し時にいたマスの成分
		
		x_center = (myself.GetX() + myself.GetX()+32) / 2;	//キャラの中心座標の計算
		y_center = (myself.GetY() + myself.GetY()+32) / 2;
		
		i_current = y_center / 32;		//中心座標のある位置を今いるマスとする
		j_current = x_center / 32;
	
		switch(/* targetRoute.empty() ? -1 : targetRoute.front()*/nextDirection )
		{
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
			case -1:
				nowExploring = 0;
				break;
			default:
				break;
		}
		//hasCalculated  = 1;
	//}//end of if block
}

int EnemyAI::GetAction(const Enemy &myself)
{

	//if(hasCalculated == 0)
	//{
	//	//次に進む場所の座標の計算
	//	CalculateNextPosition(myself, targetRoute.empty() ? -1 : targetRoute.front());
	//	hasCalculated = 1;
	//}

	////自身が一マス分の移動を終えたら
	//if(myself.GetX() == x_next && myself.GetY() == y_next /*&& nowExploring == 1*/)
	////if(myself.GetX() % 32 == 0 && myself.GetY() % 32 == 0)
	//{
	//	//次の目標マスを再計算する
	//	hasCalculated = 0;

	//	if(targetRoute.empty() == 0)
	//		targetRoute.pop_front();
	//}
	//
	//if(nowExploring == 1)
	//{
	//	if(targetRoute.empty() == 1)
	//	{
	//		return STOP;
	//	}
	//	else
	//	{
	//		return targetRoute.front();
	//	}
	//}
	//else
	//{
	//	return STOP;
	//}

	//if(myself.GetX() == x_next && myself.GetY() == y_next)
	////if(myself.GetX() % 32 == 0 && myself.GetY() % 32 == 0)
	//{
	//	if(targetRoute.empty() == 0)
	//		targetRoute.pop_front();
	//	
	//	if(targetRoute.empty() == 1)
	//		nowExploring = 0;
	//}
	//	
	//if(targetRoute.empty() == 1)
	//{
	//	return STOP;
	//}
	//else
	//{
	//	return targetRoute.front();
	//}

	if(route->GetRoute(myself) == -1)
	{
		nowExploring = 0;

		return STOP;
	}
	else 
	{
		return route->GetRoute(myself);
	}

}


