#include "StopRoute.h"
#include "Search.h"
#include "Dijkstra.h"
#include "Enemy.h"

StopRoute::StopRoute(void):
	routeList(),
	hasCalculated(0),
	x_next(0),
	y_next(0),
	search(new Search),
	dijkstra(new Dijkstra),
	i_safe(0),
	j_safe(0)
{
}


StopRoute::~StopRoute(void)
{
	delete search;
	delete dijkstra;
}

void StopRoute::DecideGoal(const Enemy &myself)
{
	search->CheckAbleToAvoidFromBomb(myself.GetY()/32, myself.GetX()/32, &i_safe, &j_safe);
}

void  StopRoute::SetRoute(const Enemy &myself)
{
	//���[�g�̏�����
	routeList.clear();

	//�ŒZ�o�H�̃Z�b�g
	dijkstra->SearchShortestPath(myself.GetY()/32, myself.GetX()/32, i_safe, j_safe, &routeList);
	routeList.push_back(STOP);
}

int StopRoute::GetRoute(const Enemy &myself)
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
	
		switch(routeList.empty() ? -1 : routeList.front())
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
				//nowExploring = 0;
				break;
			default:
				break;
		}
		hasCalculated = 1;
	}

	if(myself.GetX() == x_next && myself.GetY() == y_next )
	{
		//���̖ڕW�}�X���Čv�Z����
		hasCalculated = 0;

		if(routeList.empty() == 0)
			routeList.pop_front();
	}
	
	
		if(routeList.empty() == 1)
		{
			return -1;		//���X�g����Ȃ�I���Ƃ��ā|�P��Ԃ�
		}
		else
		{
			return routeList.front();
		}

}