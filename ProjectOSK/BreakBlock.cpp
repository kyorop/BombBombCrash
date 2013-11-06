#include "BreakBlock.h"
#include "MapState.h"
#include "DangerState.h"
#include "DxLib.h"
#include <vector>

BreakBlock::BreakBlock(IStateChanger *stateMrg)
	:State(stateMrg)
{
}


BreakBlock::~BreakBlock(void)
{
}


void BreakBlock::ChangeState()
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
				i_next = i_center;
				j_next = j_center;
				break;
		}
		if(GameConst::EnemyAction::BOMBSET == (routeList.empty() ? -1 : routeList.front()))
		{
			std::list<int> temp;
			if(search->SetEscapeRouteWhenInDanger(i_center, j_center, &temp) == 0)
			{
				routeList.clear();
				reset = 0;
			}
		}
		else if(DangerState::GetInstance()->GetDangerState(i_center, j_center) == 1)
		{
			stateMrg->ChangeState(IStateChanger::AVOID);
			routeList.clear();
			reset = 0;
		}
		else if(DangerState::GetInstance()->GetFireState(i_next, j_next) == 1 || DangerState::GetInstance()->GetDangerState(i_next, j_next) == 1)
		{
			routeList.clear();
			routeList.push_back(GameConst::EnemyAction::STOP);
			reset = 0;
		}
		
		//else if(CheckAroundMyself(i_center, j_center, MapState::CHARACTOR, 2) == 1 )
		//{
		//	stateMrg->ChangeState(IStateChanger::ATTACK);
		//	//切り替えが決まったら、これ以上移動しないようにする
		//	routeList.clear();
		//	reset = 0;
		//}
	}
}


void BreakBlock::Analyse(const Enemy &myself)
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
		std::vector<int> i_to, j_to;
		routeList.clear();
		//ルートセット
		if(search->SetGoal(i_center, j_center, &i_to, &j_to) == 1)
		{
			int rand = GetRand(i_to.size()-1);
			dijkstra->SearchShortestPath(i_center, j_center, i_to[rand], j_to[rand], &routeList);
			routeList.push_back(GameConst::EnemyAction::BOMBREADY);
			routeList.push_back(GameConst::EnemyAction::BOMBSET);
			reset = 0;
		}
	}
}