#include "Avoid.h"
#include "Search.h"
#include "Dijkstra.h"
#include "Enemy.h"
#include "MapState.h"
#include "DangerState.h"

using namespace BombBombCrash;

Avoid::Avoid(IStateChanger *stateMrg, const Enemy& myself)
	:State(stateMrg, myself)
{
}


Avoid::~Avoid(void)
{
}


void Avoid::ChangeState()
{
	int i_next, j_next;
	int i_current = y_next / 32;		//現在の移動が完了した時にいる場所
	int j_current = x_next / 32;
	switch(routeList.empty() ? -1 : routeList.front())
	{
		case GameConst::EnemyAction::UP:
			i_next = i_current-1;
			j_next = j_current;
			break;
		case GameConst::EnemyAction::DOWN:
			i_next = i_current+1;
			j_next = j_current;
			break;
		case GameConst::EnemyAction::LEFT:
			i_next = i_current;
			j_next = j_current-1;
			break;
		case GameConst::EnemyAction::RIGHT:
			i_next = i_current;
			j_next = j_current+1;
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
		resetRoute = 1;
	}
	else if(search->CheckInClosedInterval(i_center, j_center) == 1)
	{
		//上の条件を抜けてきたから危険地にはいない
		routeList.clear();
		routeList.push_back(GameConst::EnemyAction::STOP);
		resetRoute = 0;
	}else if(search->CheckInClosedInterval(i_next, j_next) == 1)
	{
		routeList.clear();
		resetRoute = 1;
	}
	else if(CheckAroundMyself(i_center, j_center, MapState::CHARACTOR, scoutingRadius_character))
		stateMrg->ChangeState(IStateChanger::ATTACK);
	else if(CheckAroundMyself(i_center, j_center, MapState::ITEM, scoutingRadius_item))
		stateMrg->ChangeState(IStateChanger::GETITEM);
	else
		stateMrg->ChangeState(IStateChanger::BREAKBLOCK);
}


void Avoid::Analyse()
{
	UpdateCoordinate();
	
	if(routeList.empty())
		resetRoute = 1;

	ChangeState();
	
	if(resetRoute == 1)
	{
		routeList.clear();
		//ルートセット
		if(search->SetEscapeRouteWhenInDanger(myself.GetY()/32, myself.GetX()/32, &routeList) == 1)
		{
			routeList.push_back(GameConst::EnemyAction::STOP);
			resetRoute = 0;
		}
	}

	
}