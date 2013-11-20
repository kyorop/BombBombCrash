#include "AttackOtherCharacter.h"
#include "MapState.h"
#include "DangerState.h"
#include "GameConstant.h"

AttackOtherCharacter::AttackOtherCharacter(IStateChanger *stateMrg, const Enemy& myself)
	:State(stateMrg, myself)
{
}


AttackOtherCharacter::~AttackOtherCharacter(void)
{
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


int AttackOtherCharacter::CheckCharacterInSameRowOrLine(int i_now, int j_now)
{
	for(int j=0; j<GameConst::MAP_LINE; ++j)
	{
		if(MapState::GetInstance()->GetState(i_now, j, MapState::CHARACTOR))
			return 1;
	}
	for(int i=0; i<GameConst::MAP_ROW; ++i)
	{
		if(MapState::GetInstance()->GetState(i, j_now, MapState::CHARACTOR))
			return 1;
	}

	return 0;
}


void AttackOtherCharacter::ChangeState()
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
	else if(MapState::GetInstance()->GetState(i_next, j_next, MapState::FIRE) == 1 || DangerState::GetInstance()->GetFireState(i_next, j_next) == 1 || DangerState::GetInstance()->GetDangerState(i_next, j_next) == 1)
	{
		stateMrg->ChangeState(IStateChanger::AVOID);
		routeList.clear();
		resetRoute = 0;
	}
}


void AttackOtherCharacter::Analyse()
{
	UpdateCoordinate();

	if(routeList.empty())
		routeList.clear();
	
	ChangeState();

	if(resetRoute == 1)
	{
		int i_to;
		int j_to;
		if(CheckCharacterAroundMyself(i_center, j_center, &i_to, &j_to))
		{
			dijkstra->SearchShortestPath(i_center, j_center, i_to, j_to, &routeList);
			routeList.push_back(GameConst::EnemyAction::BOMBSET);
			resetRoute = 0;
		}
	}
	else if(CheckCharacterInSameRowOrLine(i_center, j_center))
	{
		routeList.push_front(GameConst::EnemyAction::BOMBSET);
	}
}