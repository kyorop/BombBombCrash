#include "BreakBlock.h"
#include "MapState.h"
#include "DangerState.h"
#include <vector>

BreakBlock::BreakBlock(IStateChanger *stateMrg, const Enemy& myself)
	:State(stateMrg, myself)
{
}


BreakBlock::~BreakBlock(void)
{
}


void BreakBlock::ChangeState()
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

	if(GameConst::EnemyAction::BOMBSET == (routeList.empty() ? -1 : routeList.front()))
	{
		std::list<int> temp;
		if(search->SetEscapeRouteWhenInDanger(i_center, j_center, &temp) == 0)
		{
			routeList.clear();
			resetRoute = 0;
		}
	}
	else if(DangerState::GetInstance()->GetDangerState(i_center, j_center))
	{
		stateMrg->ChangeState(IStateChanger::AVOID);
	}
	else if(MapState::GetInstance()->GetState(i_next, j_next, MapState::FIRE) == 1 || DangerState::GetInstance()->GetFireState(i_next, j_next) == 1 || DangerState::GetInstance()->GetDangerState(i_next, j_next) == 1)
	{
		routeList.clear();
		routeList.push_back(GameConst::EnemyAction::STOP);
		resetRoute = 0;
	}
	else if(CheckAroundMyself(i_center, j_center, MapState::CHARACTOR, scoutingRadius_character))
	{
		stateMrg->ChangeState(IStateChanger::ATTACK);
	}
	else if(CheckAroundMyself(i_center, j_center, MapState::ITEM, scoutingRadius_item))
	{
		stateMrg->ChangeState(IStateChanger::GETITEM);
	}
}


void BreakBlock::Analyse()
{
	UpdateCoordinate();
	
	if(routeList.empty())
		resetRoute = 1;
	
	ChangeState();
	
	if(resetRoute == 1)
	{
		std::vector<int> i_to, j_to;
		routeList.clear();
		//ルートセット
		if(search->SetGoal(i_center, j_center, &i_to, &j_to))
		{
			int rand = GetRand(i_to.size()-1);
			dijkstra->SearchShortestPath(i_center, j_center, i_to[rand], j_to[rand], &routeList);
			routeList.push_back(GameConst::EnemyAction::BOMBREADY);
			routeList.push_back(GameConst::EnemyAction::BOMBSET);
			resetRoute = 0;
		}
	}
	
	
}