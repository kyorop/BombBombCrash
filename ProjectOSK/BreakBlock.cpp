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
		if(DangerState::GetInstance()->GetDangerState(i_center, j_center) == 1)
		{
			stateMrg->ChangeState(IStateChanger::AVOID);
			routeList.clear();
			reset = 0;
		}
		else if(CheckAroundMyself(i_center, j_center, MapState::CHARACTOR, 2) == 1 )
		{
			stateMrg->ChangeState(IStateChanger::ATTACK);
			//切り替えが決まったら、これ以上移動しないようにする
			routeList.clear();
			reset = 0;
		}
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
			//routeList.push_back(GameConst::EnemyAction::BOMBSET);
			reset = 0;
		}
	}
}