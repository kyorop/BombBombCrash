#include "State.h"
#include "Search.h"
#include "Dijkstra.h"
#include "Enemy.h"
#include "GameConstant.h"
#include "MapState.h"

State::State(IStateChanger *stateMrg, const Enemy &myself)
	:stateMrg(stateMrg),
	routeList(),
	search(new Search),
	dijkstra(new Dijkstra),
	myself(myself),
	i_center(-1),
	j_center(-1),
	x_next(-1),
	y_next(-1),
	resetRoute(1),
	currentAction(-1),
	resetCalc(1)
{
}


State::~State(void)
{
	delete dijkstra;
	delete search;
}


int State::CheckAroundMyself(int i_now, int j_now/*, int* i_to, int* j_to*/, int TRAGET, int radius)
{
	int success = 0;
	for(int i=i_now-radius; i<=i_now+radius; ++i)
	{
		for(int j=j_now-radius; j<=j_now+radius; ++j)
		{
			if(i != i_now && j != j_now)
			{
				if(MapState::GetInstance()->GetState(i, j, TRAGET) == 1)//他のキャラクターを見つけたら
				{
					if(search->CheckAbleToGoTo(i_now, j_now, i, j) == 1)//そこに行けるか調べて
					{
						//*i_to = i;
						//*j_to = j;
						success = 1;
					}
				}
			}
		}
	}

	return success;
}


int State::GetRoute()
{	
	if(myself.GetX() == x_next && myself.GetY() == y_next)
		resetCalc = 1;

	if(resetCalc == 1)
	{
		//次に進む場所の座標の計算
		int x_center, y_center;
		int i_current, j_current;		//呼び出し時にいたマスの成分
		
		x_center = (myself.GetX() + myself.GetX()+32) / 2;	//キャラの中心座標の計算
		y_center = (myself.GetY() + myself.GetY()+32) / 2;
		
		i_current = y_center / 32;		//中心座標のある位置を今いるマスとする
		j_current = x_center / 32;
	
		if( !routeList.empty() )
		{
			switch( routeList.front() )
			{
			case GameConst::EnemyAction::STOP:
				currentAction = routeList.front();
				routeList.pop_front();
				break;
			case GameConst::EnemyAction::UP:
				x_next = (j_current + 0) * 32;
				y_next = (i_current - 1) * 32;
				currentAction = routeList.front();
				routeList.pop_front();
				resetCalc = 0;
				break;
			case GameConst::EnemyAction::DOWN:
				x_next = (j_current + 0) * 32;
				y_next = (i_current + 1) * 32;
				currentAction = routeList.front();
				routeList.pop_front();
				resetCalc = 0;
				break;
			case GameConst::EnemyAction::LEFT:
				x_next = (j_current - 1) * 32;
				y_next = (i_current + 0) * 32;
				currentAction = routeList.front();
				routeList.pop_front();
				resetCalc = 0;
				break;
			case GameConst::EnemyAction::RIGHT:
				x_next = (j_current + 1) * 32;
				y_next = (i_current + 0) * 32;
				currentAction = routeList.front();
				routeList.pop_front();
				resetCalc = 0;
				break;
			case GameConst::EnemyAction::BOMBREADY:
				routeList.pop_front();
				currentAction = GameConst::EnemyAction::STOP;
				break;
			case GameConst::EnemyAction::BOMBSET:
				currentAction = routeList.front();
				routeList.pop_front();
				break;
			default:
				break;
			}
		}
	}

	return currentAction;
}
