#include "State.h"
#include "Search.h"
#include "Dijkstra.h"
#include "Enemy.h"
#include "GameConstant.h"
#include "MapState.h"
#include "DangerState.h"

using namespace BombBombCrash;

State::State(IStateChanger *stateMrg, const Enemy &myself)
	:stateMrg(stateMrg),
	routeList(),
	search(new Search),
	dijkstra(new Dijkstra),
	myself(myself),
	i_center(-1),
	j_center(-1),
	x_next(-1),
	y_next(-1),
	resetRoute(1),
	currentAction(-1),
	resetCalc(1)
{
}


State::~State(void)
{
	delete dijkstra;
	delete search;
}


void State::UpdateCoordinate()
{
	x_center = (myself.X()+myself.X()+32)/2;
	y_center = (myself.Y()+myself.Y()+32)/2;
	i_center = y_center/32;
	j_center = x_center/32;
}

int State::CheckAroundMyself(int i_now, int j_now, int TRAGET, int radius)
{
	int success = 0;
	for(int i=i_now-radius; i<=i_now+radius; ++i)
	{
		for(int j=j_now-radius; j<=j_now+radius; ++j)
		{
			if(i != i_now && j != j_now)
			{
				if(MapState::GetInstance()->GetState(i, j, TRAGET) == 1)//���̃L�����N�^�[���������
				{
					if(search->CheckAbleToGoTo(i_now, j_now, i, j) == 1)//�����ɍs���邩���ׂ�
					{
						success = 1;
					}
				}
			}
		}
	}

	return success;
}


int State::CheckObjectAroundAndAbleToGoThere(int i_now, int j_now, int* i_to, int* j_to, int OBJECT, int radius)
{
	for(int i=i_now-radius; i<=i_now+radius; ++i)
	{
		for(int j=j_now-radius; j<=j_now+radius; ++j)
		{
			if(i != i_now && j != j_now)
			{
				if(MapState::GetInstance()->GetState(i, j, OBJECT))//���̃L�����N�^�[���������
				{
					if(search->CheckAbleToGoTo(i_now, j_now, i, j))//�����ɍs���邩���ׂ�
					{
						*i_to = i;
						*j_to = j;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}


void State::ChangeStateBase()
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

	if(MapState::GetInstance()->GetState(i_next, j_next, MapState::FIRE) == 1 || DangerState::GetInstance()->GetDangerState(i_next, j_next) == 1)
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
	else
	{
		stateMrg->ChangeState(IStateChanger::BREAKBLOCK);
	}
}

int State::GetRoute()
{	
	if(myself.X() == x_next && myself.Y() == y_next)
		resetCalc = 1;

	if(resetCalc == 1)
	{
		//���ɐi�ޏꏊ�̍��W�̌v�Z
		int x_center, y_center;
		int i_current, j_current;		//�Ăяo�����ɂ����}�X�̐���
		
		x_center = (myself.X() + myself.X()+32) / 2;	//�L�����̒��S���W�̌v�Z
		y_center = (myself.Y() + myself.Y()+32) / 2;
		
		i_current = y_center / 32;		//���S���W�̂���ʒu�������}�X�Ƃ���
		j_current = x_center / 32;
	
		if( !routeList.empty() )
		{
			switch( routeList.front() )
			{
			case BombBombCrash::EnemyAction::STOP:
				currentAction = routeList.front();
				routeList.pop_front();
				break;
			case BombBombCrash::EnemyAction::UP:
				x_next = (j_current + 0) * 32;
				y_next = (i_current - 1) * 32;
				currentAction = routeList.front();
				routeList.pop_front();
				resetCalc = 0;
				break;
			case BombBombCrash::EnemyAction::DOWN:
				x_next = (j_current + 0) * 32;
				y_next = (i_current + 1) * 32;
				currentAction = routeList.front();
				routeList.pop_front();
				resetCalc = 0;
				break;
			case BombBombCrash::EnemyAction::LEFT:
				x_next = (j_current - 1) * 32;
				y_next = (i_current + 0) * 32;
				currentAction = routeList.front();
				routeList.pop_front();
				resetCalc = 0;
				break;
			case BombBombCrash::EnemyAction::RIGHT:
				x_next = (j_current + 1) * 32;
				y_next = (i_current + 0) * 32;
				currentAction = routeList.front();
				routeList.pop_front();
				resetCalc = 0;
				break;
			case BombBombCrash::EnemyAction::BOMBREADY:
				routeList.pop_front();
				currentAction = BombBombCrash::EnemyAction::STOP;
				break;
			case BombBombCrash::EnemyAction::BOMBSET:
				currentAction = routeList.front();
				routeList.pop_front();
				break;
			default:
				break;
			}
		}
	}

	return currentAction;
}
