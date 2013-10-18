#include "Avoid.h"
#include "Search.h"
#include "Dijkstra.h"
#include "Enemy.h"

Avoid::Avoid(void):
	search(new Search),
	dijkstra(new Dijkstra),
	i_safe(),
	j_safe(),
	routeList(),
	hasCalculated(0),
	x_next(),
	y_next()
{
	myclass = 2;
}

Avoid::~Avoid(void)
{
	delete search;
	delete dijkstra;
}

void Avoid::DecideGoal(const Enemy &myself)
{
	hasCalculated = 0;
}

void Avoid::SetRoute(const Enemy &myself)
{
	//������
	routeList.clear();

	//���[�g�Z�b�g
	if(search->SetEscapeRouteWhenInDanger(myself.GetY()/32, myself.GetX()/32, &routeList) == 0)
	{
	}
	//routeList.push_back(STOP);
}

int Avoid::GetRoute(const Enemy &myself)
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
			switch( routeList.front() )
			{
				case UP:
					x_next = (j_current + 0) * 32;
					y_next = (i_current - 1) * 32;
					break;
				case DOWN:
					x_next = (j_current + 0) * 32;
					y_next = (i_current + 1) * 32;
					break;
				case LEFT:
					x_next = (j_current - 1) * 32;
					y_next = (i_current + 0) * 32;
					break;
				case RIGHT:
					x_next = (j_current + 1) * 32;
					y_next = (i_current + 0) * 32;
					break;
				case -1:
					return -1;
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

		if( !routeList.empty() )
			routeList.pop_front();
	}
	
	
	if( routeList.empty() )
	{
		return -1;		//���X�g����Ȃ�I���Ƃ��ā|�P��Ԃ�
	}
	else
	{
		return routeList.front();
	}

}