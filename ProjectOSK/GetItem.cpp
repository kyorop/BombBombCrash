#include "GetItem.h"
#include "MapState.h"
#include "DangerState.h"


GetItem::GetItem(IStateChanger *stateMrg, const Enemy& myself)
	:State(stateMrg, myself)
{
}


GetItem::~GetItem(void)
{
}


void GetItem::ChangeState()
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
		stateMrg->ChangeState(IStateChanger::AVOID);
		routeList.clear();
		resetRoute = 0;
	}
	else if(DangerState::GetInstance()->GetDangerState(i_next, j_next) == 1)
	{
		stateMrg->ChangeState(IStateChanger::AVOID);
		routeList.clear();
		resetRoute = 0;
	}
	else if(MapState::GetInstance()->GetState(i_next, j_next, MapState::FIRE) == 1 
			|| DangerState::GetInstance()->GetFireState(i_next, j_next) == 1 
			|| DangerState::GetInstance()->GetDangerState(i_next, j_next) == 1)
	{
		stateMrg->ChangeState(IStateChanger::AVOID);
		routeList.clear();
		resetRoute = 0;
	}
}


void GetItem::Analyse()
{
	UpdateCoordinate();
	
	if(routeList.empty())
		resetRoute = 1;
	
	ChangeState();
	
	if(resetRoute == 1)
	{
		routeList.clear();
		//ルートセット
		int i_to;
		int j_to;
		if(CheckObjectAroundAndAbleToGoThere(i_center, j_center, &i_to, &j_to,MapState::ITEM, 8))
		{
			dijkstra->SearchShortestPath(i_center, j_center, i_to, j_to, &routeList);
		}
	}
}