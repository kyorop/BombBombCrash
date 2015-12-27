#include "GetItem.h"
#include "MapState.h"
#include "DangerState.h"

using namespace BombBombCrash;

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
	int i_current = y_next / 32;		//���݂̈ړ��������������ɂ���ꏊ
	int j_current = x_next / 32;
	switch(routeList.empty() ? -1 : routeList.front())
	{
		case BombBombCrash::EnemyAction::UP:
			i_next = i_current-1;
			j_next = j_current;
			break;
		case BombBombCrash::EnemyAction::DOWN:
			i_next = i_current+1;
			j_next = j_current;
			break;
		case BombBombCrash::EnemyAction::LEFT:
			i_next = i_current;
			j_next = j_current-1;
			break;
		case BombBombCrash::EnemyAction::RIGHT:
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
		//���[�g�Z�b�g
		int i_to;
		int j_to;
		if(CheckObjectAroundAndAbleToGoThere(i_center, j_center, &i_to, &j_to,MapState::ITEM, 8))
		{
			dijkstra->SearchShortestPath(i_center, j_center, i_to, j_to, &routeList);
		}
	}
}