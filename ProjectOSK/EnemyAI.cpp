#include "EnemyAI.h"
#include "MapState.h"
#include "Enemy.h"
#include "Dijkstra.h"
#include "Search.h"
#include "Route.h"
#include "Target.h"
#include "Avoid.h"
#include "StopRoute.h"
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
	hasCalculated(0),
	nowExploring(0),
	target(new Target),
	avoid(new Avoid),
	stop(new StopRoute),
	route(target),
	search(new Search)
{
}

EnemyAI::~EnemyAI(void)
{
	delete target;
	delete avoid;
}

int EnemyAI::CheckBombCAroundMyself(const Enemy &myself)
{
	int i_current = myself.GetY() / 32;
	int j_current = myself.GetX() / 32;

	for (int j = j_current; j < GameConst::MAP_LINE; ++j)
	{
		if(MapState::GetInstance()->GetState(i_current, j, MAP) == 1 || MapState::GetInstance()->GetState(i_current, j, BLOCK) == 1)
			break;
		if(MapState::GetInstance()->GetState(i_current, j, BOMB) == 1)
		{
			if(route == target)
			{
				route = stop;
				return 1;
			}
		}
	}
	for (int j = j_current; j >= 0;  --j)
	{
		if(MapState::GetInstance()->GetState(i_current, j, MAP) == 1 || MapState::GetInstance()->GetState(i_current, j, BLOCK) == 1)
			break;
		if(MapState::GetInstance()->GetState(i_current, j, BOMB) == 1)
		{
			if(route == target)
			{
				route = stop;
				return 1;
			}
		}
	}

	for (int i = i_current; i < GameConst::MAP_ROW; ++i)
	{
		if(MapState::GetInstance()->GetState(i, j_current, MAP) == 1 || MapState::GetInstance()->GetState(i, j_current, BLOCK) == 1)
			break;
		if(MapState::GetInstance()->GetState(i, j_current, BOMB) == 1)
		{
			if(route == target)
			{
				route = stop;
				//break;
				return 1;
			}
		}
	}

	for (int i = i_current; i >= 0; --i)
	{
		if(MapState::GetInstance()->GetState(i, j_current, MAP) == 1 || MapState::GetInstance()->GetState(i, j_current, BLOCK) == 1)
			break;
		if(MapState::GetInstance()->GetState(i, j_current, BOMB) == 1)
		{
			if(route == target)
			{
				route = stop;
				//break;
				return 1;
			}
		}
	}

	return 0;
}

int EnemyAI::CheckDanager(const Enemy &myself)
{
	if(MapState::GetInstance()->GetDangerState(myself.GetY()/32, myself.GetX()/32) == 1)
		return 1;
	else
		return 0;
}

int EnemyAI::CheckAbleToMove(const Enemy &myself)
{
	return 0;
}

void EnemyAI::Analyse(int i_current, int j_current, const Enemy &myself)
{
	//int x_center = myself.GetX() + myself.GetX() + 32;
	//int y_center = myself.GetY() + myself.GetY() + 32;

	//ちょうどマスぴったりにいるときに
	/*if(myself.GetX() % 32 == 0 && myself.GetY() % 32 == 0)*/
	//{
		//if(search->CheckInClosedInterval(myself.GetY()/32, myself.GetX()/32) == 1 && myself.GetX() % 32 == 0 && myself.GetY() % 32 == 0)
		//{
		//	route = stop;	//閉区間にいるならストップ
		//	nowExploring = 0;
		//}
		//else if(CheckDanager(myself) == 1)
		//{
		//	route = avoid;	//危険地にいるなら逃げる
		//	nowExploring = 0;
		//}
		//else
		//{
		//	route = target;	//どれでもないならターゲットを狙う
		//	//nowExploring = 0;
		//}
	//}

	if(nowExploring == 0)
	{
		//if(myself.GetX() % 32 == 0 && myself.GetY() % 32 == 0)
		{
			route->DecideGoal(myself);
			route->SetRoute(myself);
			nowExploring = 1;
		}
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
	if(nowExploring == 1)
	{
		//ルートがなくなったら思考停止
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
	else
		return STOP;	//思考中という意味
}


