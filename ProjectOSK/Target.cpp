#include "Target.h"
#include "Search.h"
#include "Dijkstra.h"
#include "Enemy.h"
#include "DxLib.h"

Target::Target(void):
	i_to(),
	j_to(),
	rand(),
	routeList(),
	search(new Search),
	dijkstra(new Dijkstra),
	hasCalculated(0)
{
}

Target::~Target(void)
{
	delete search;
	delete dijkstra;
}

void Target::DecideGoal(const Enemy &myself)
{
	//������
	i_to.clear();
	j_to.clear();

	//�ړI�n�̌���
	search->SetGoalInitialized(myself.GetY()/32, myself.GetX()/32, &i_to, &j_to);
	
	rand = GetRand(i_to.size() - 1);
}

void Target::SetRoute(const Enemy &myself)
{
	//������
	routeList.clear();

	//�ŒZ�o�H�̃Z�b�g
	dijkstra->SearchShortestPath(myself.GetY()/32, myself.GetX()/32, i_to[rand], j_to[rand], &routeList);
}

int Target::GetRoute(const Enemy &myself)
{
	if(hasCalculated == 0)	//��x�v�Z������A��}�X�ړ����I���܂ōČv�Z���Ȃ�
	{
		int x_center, y_center;
		int i_current, j_current;		//�Ăяo�����ɂ����}�X�̐���
		
		x_center = (myself.GetX() + myself.GetX()+32) / 2;	//�L�����̒��S���W�̌v�Z
		y_center = (myself.GetY() + myself.GetY()+32) / 2;
		
		i_current = y_center / 32;		//���S���W�̂���ʒu��������}�X�Ƃ���
		j_current = x_center / 32;
	
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
		}
		hasCalculated  = 1;
	}//end of if block

	if(myself.GetX() == x_next && myself.GetY() == y_next)
	{
		routeList.pop_front();
		hasCalculated = 0;		//���̈ړ���̍��W���Čv�Z
	}

	if(routeList.empty() == 1)
	{
		return -1;
	}
	else
	{
		return routeList.front();
	}
}