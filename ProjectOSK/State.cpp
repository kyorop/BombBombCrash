#include "State.h"
#include "Search.h"
#include "Dijkstra.h"
#include "Enemy.h"
#include "GameConstant.h"
#include "MapState.h"

State::State(IStateChanger *stateMrg)
	:stateMrg(stateMrg),
	routeList(),
	search(new Search),
	dijkstra(new Dijkstra),
	x_now(-1),
	y_now(-1),
	i_center(-1),
	j_center(-1),
	hasCalculated(0),
	x_next(-1),
	y_next(-1),
	reset(1)
{
}


State::~State(void)
{
	delete dijkstra;
	delete search;
}


int State::CheckAroundMyself(int i_now, int j_now/*, int* i_to, int* j_to*/, int TRAGET, int radius)
{
	int success = 0;
	for(int i=i_now-radius; i<=i_now+radius; ++i)
	{
		for(int j=j_now-radius; j<=j_now+radius; ++j)
		{
			if(i != i_now && j != j_now)
			{
				if(MapState::GetInstance()->GetState(i, j, TRAGET) == 1)//���̃L�����N�^�[����������
				{
					if(search->CheckAbleToGoTo(i_now, j_now, i, j) == 1)//�����ɍs���邩���ׂ�
					{
						//*i_to = i;
						//*j_to = j;
						success = 1;
					}
				}
			}
		}
	}

	return success;
}

int State::GetRoute(const Enemy &myself)
{
	if(hasCalculated == 0)
	{
		//���ɐi�ޏꏊ�̍��W�̌v�Z
		int x_center, y_center;
		int i_current, j_current;		//�Ăяo�����ɂ����}�X�̐���
		
		x_center = (myself.GetX() + myself.GetX()+32) / 2;	//�L�����̒��S���W�̌v�Z
		y_center = (myself.GetY() + myself.GetY()+32) / 2;
		
		i_current = y_center / 32;		//���S���W�̂���ʒu��������}�X�Ƃ���
		j_current = x_center / 32;
	
		if( !routeList.empty() )
		{
			switch(routeList.empty() ? -1 : routeList.front())
			{
			case GameConst::EnemyAction::UP:
				x_next = (j_current + 0) * 32;
				y_next = (i_current - 1) * 32;
				break;
			case GameConst::EnemyAction::DOWN:
				x_next = (j_current + 0) * 32;
				y_next = (i_current + 1) * 32;
				break;
			case GameConst::EnemyAction::LEFT:
				x_next = (j_current - 1) * 32;
				y_next = (i_current + 0) * 32;
				break;
			case GameConst::EnemyAction::RIGHT:
				x_next = (j_current + 1) * 32;
				y_next = (i_current + 0) * 32;
				break;
			case GameConst::EnemyAction::BOMBSET:
				routeList.pop_front();
				return GameConst::EnemyAction::BOMBSET;
			default:
				return -1;
			}
		}
		hasCalculated = 1;
	}

	if(myself.GetX() == x_next && myself.GetY() == y_next)
	{
		//���̖ڕW�}�X���Čv�Z����
		hasCalculated = 0;

		if(routeList.empty() == 0)
			routeList.pop_front();
	}

	if( routeList.empty() )
	{
		reset = 1;
		return -1;		//���X�g����Ȃ�I��(�G���[)�Ƃ��ā|�P��Ԃ�
	}
	else
	{
		return routeList.front();
	}
}
