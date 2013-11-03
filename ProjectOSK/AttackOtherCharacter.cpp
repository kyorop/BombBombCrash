#include "AttackOtherCharacter.h"
#include "MapState.h"
#include "DangerState.h"
#include "GameConstant.h"

AttackOtherCharacter::AttackOtherCharacter(IStateChanger *stateMrg)
	:State(stateMrg)
{
}


AttackOtherCharacter::~AttackOtherCharacter(void)
{
}


void AttackOtherCharacter::ChangeState()
{
	//キャラクターがちょうどマスピッタリにいる時だけステートの切り替えを行う
	if(x_now%32 == 0 && y_now%32 == 0)
	{
		if(search->CheckInClosedInterval(i_center, j_center) == 1 && DangerState::GetInstance()->GetDangerState(i_center, j_center) == 0)
		{
			stateMrg->ChangeState(IStateChanger::AVOID);
			
			//切り替えが決まったら、これ以上移動しないようにする
			routeList.clear();
			reset = 0;
		}
	}
}


int AttackOtherCharacter::CheckCharacterAroundMyself(int i_now, int j_now, int* i_to, int* j_to)
{
	int success = 0;
	for(int i=i_now-radiusOfSearch; i<=i_now+radiusOfSearch; ++i)
	{
		for(int j=j_now-radiusOfSearch; j<=j_now+radiusOfSearch; ++j)
		{
			if(i != i_now && j != j_now)
			{
				if(MapState::GetInstance()->GetState(i, j, MapState::CHARACTOR) == 1)//他のキャラクターを見つけたら
				{
					if(search->CheckAbleToGoTo(i_now, j_now, i, j) == 1)//そこに行けるか調べて
					{
						*i_to = i;
						*j_to = j;
						success = 1;
					}
				}
			}
		}
	}

	return success;
}


void AttackOtherCharacter::Analyse(const Enemy &myself)
{
	ChangeState();
	//初期化
	routeList.clear();

	x_center = (myself.GetX()+myself.GetX()+32)/2;
	y_center = (myself.GetY()+myself.GetY()+32)/2;
	i_center = y_center/32;
	j_center = x_center/32;

	if(reset == 1)
	{
		int i_to;
		int j_to;
		if(CheckCharacterAroundMyself(i_center, j_center, &i_to, &j_to) == 1)
		{
			dijkstra->SearchShortestPath(i_center, j_center, i_to, j_to, &routeList);
			routeList.push_back(GameConst::EnemyAction::BOMBSET);
			reset = 0;
		}
	}
}