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
		//�܂��댯�n�тɂ��邩�獡�̏�Ԃ�p��
	}
	else if(DangerState::GetInstance()->GetFireState(i_next, j_next) == 1 || DangerState::GetInstance()->GetDangerState(i_next, j_next) == 1)
	{
		resetRoute = 1;
	}
	else if(search->CheckInClosedInterval(i_center, j_center) == 1)
	{
		//��̏���𔲂��Ă�������댯�n�ɂ͂��Ȃ�
		routeList.clear();
		routeList.push_back(BombBombCrash::EnemyAction::STOP);
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
		//���[�g�Z�b�g
		if(search->SetEscapeRouteWhenInDanger(myself.Y()/32, myself.X()/32, &routeList) == 1)
		{
			routeList.push_back(BombBombCrash::EnemyAction::STOP);
			resetRoute = 0;
		}
	}

	
}