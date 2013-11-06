#include "Avoid.h"
#include "Search.h"
#include "Dijkstra.h"
#include "Enemy.h"
#include "MapState.h"
#include "DangerState.h"

Avoid::Avoid(IStateChanger *stateMrg)
	:State(stateMrg)
{
}

Avoid::~Avoid(void)
{
}


void Avoid::ChangeState()
{
	//キャラクターがちょうどマスピッタリにいる時だけステートの切り替えを行う
	if(x_now%32 == 0 && y_now%32 == 0)
	{
		int i_next;
		int j_next;
		switch(routeList.empty() ? -1 : routeList.front())
		{
			case GameConst::EnemyAction::UP:
				i_next = i_center-1;
				j_next = j_center;
				break;
			case GameConst::EnemyAction::DOWN:
				i_next = i_center+1;
				j_next = j_center;
				break;
			case GameConst::EnemyAction::LEFT:
				i_next = i_center;
				j_next = j_center-1;
				break;
			case GameConst::EnemyAction::RIGHT:
				i_next = i_center;
				j_next = j_center+1;
				break;
			default:
				i_next = -1;
				j_next = -1;
				break;
		}
		if(DangerState::GetInstance()->GetDangerState(i_center, j_center) == 1)
		{
			//まだ危険地帯にいるから今の状態を継続
		}
		else if(DangerState::GetInstance()->GetFireState(i_next, j_next) == 1 || DangerState::GetInstance()->GetDangerState(i_next, j_next) == 1)
		{
			reset = 1;
		}
		else if(search->CheckInClosedInterval(i_center, j_center) == 1)
		{
			//上の条件を抜けてきたから危険地にはいない
			routeList.clear();
			routeList.push_back(GameConst::EnemyAction::STOP);
			reset = 0;
		}
		else/* if(CheckAroundMyself(i_center, j_center, MapState::BLOCK, 8) == 1 )*/
		{
			stateMrg->ChangeState(IStateChanger::BREAKBLOCK);
			
			//切り替えが決まったら、これ以上移動しないようにする
			routeList.clear();
			reset = 0;
		}
	}
}


void Avoid::Analyse(const Enemy &myself)
{
	x_now = myself.GetX();
	y_now = myself.GetY();
	x_center = (myself.GetX()+myself.GetX()+32)/2;
	y_center = (myself.GetY()+myself.GetY()+32)/2;
	i_center = y_center/32;
	j_center = x_center/32;
	
	if(routeList.empty())
		reset = 1;

	ChangeState();
	
	if(reset == 1)
	{
		routeList.clear();
		//ルートセット
		if(search->SetEscapeRouteWhenInDanger(y_now/32, x_now/32, &routeList) == 1)
		{
			routeList.push_back(GameConst::EnemyAction::STOP);
			reset = 0;
		}
	}
}