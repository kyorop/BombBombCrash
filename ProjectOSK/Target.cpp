#include "Target.h"
#include "Search.h"
#include "Dijkstra.h"
#include "Enemy.h"
#include "GameConstant.h"
#include "DxLib.h"

Target::Target(void):
	i_to(),
	j_to(),
	rand(0),
	routeList(),
	search(new Search),
	dijkstra(new Dijkstra),
	hasCalculated(0),
	x_next(-1),
	y_next(-1)
{
	myclass = 1;
}

Target::~Target(void)
{
	delete search;
	delete dijkstra;
}

void Target::DecideGoal(const Enemy &myself)
{
}

void Target::SetRoute(const Enemy &myself)
{
	//������
	i_to.clear();
	j_to.clear();

	int x_center = (myself.GetX()+myself.GetX()+32)/2;
	int y_center = (myself.GetY()+myself.GetY()+32)/2;

	//������
	routeList.clear();

	if(search->SetGoal(y_center/32, x_center/32, &i_to, &j_to) == 1)
	{
		//�ړI�n�͌��̓����痐���Ō��߂�
		rand = GetRand(i_to.size() - 1);

		int x_center = (myself.GetX()+myself.GetX()+32)/2;
		int y_center = (myself.GetY()+myself.GetY()+32)/2;

		//�ŒZ�o�H�̃Z�b�g
		//dijkstra->SearchShortestPath(myself.GetY()/32, myself.GetX()/32, i_to[rand], j_to[rand], &routeList);
		dijkstra->SearchShortestPath(y_center/32, x_center/32, i_to[rand], j_to[rand], &routeList);
		//routeList.push_back(-1);
		routeList.push_back(BOMBSET);
	}
	else
	{
		routeList.push_back(-1);
	}

	
	//if(routeList.empty() == 0)
	//{
	//	
	//	routeList.push_back(BOMBSETOFF);
	//}
}

int Target::GetRoute(const Enemy &myself)
{
	//if(hasCalculated == 0)	//��x�v�Z������A��}�X�ړ����I���܂ōČv�Z���Ȃ�
	//{
	//	int x_center, y_center;
	//	int i_current, j_current;		//�Ăяo�����ɂ����}�X�̐���
	//	
	//	x_center = (myself.GetX() + myself.GetX()+32) / 2;	//�L�����̒��S���W�̌v�Z
	//	y_center = (myself.GetY() + myself.GetY()+32) / 2;
	//	
	//	i_current = y_center / 32;		//���S���W�̂���ʒu��������}�X�Ƃ���
	//	j_current = x_center / 32;
	//
	//	switch( routeList.empty() ? -1 : routeList.front()  )
	//	{
	//		case UP:
	//			x_next = (j_current + 0) * 32;
	//			y_next = (i_current - 1) * 32;
	//			break;
	//		case DOWN:
	//			x_next = (j_current + 0) * 32;
	//			y_next = (i_current + 1) * 32;
	//			break;
	//		case LEFT:
	//			x_next = (j_current - 1) * 32;
	//			y_next = (i_current + 0) * 32;
	//			break;
	//		case RIGHT:
	//			x_next = (j_current + 1) * 32;
	//			y_next = (i_current + 0) * 32;
	//			break;
	//		default:
	//			break;
	//	}
	//	hasCalculated  = 1;
	//}//end of if block

	////���g����}�X���̈ړ����I������
	//if(myself.GetX() == x_next && myself.GetY() == y_next)
	//{
	//	if(routeList.empty() != 1)
	//	{
	//		routeList.pop_front();
	//	}
	//	hasCalculated = 0;		//���̈ړ���̍��W���Čv�Z
	//}

	//if(routeList.empty() == 1)
	//{
	//	return -1;
	//}
	//else
	//{
	//	return routeList.front();
	//}

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
				return BOMBSET;
			//case BOMBSETOFF:
			//	routeList.pop_front();
			//	return BOMBSETOFF;
			default:
				return -1;
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
	
	if(routeList.empty() == 1)
	{
		return -1;		//���X�g����Ȃ�I���Ƃ��ā|�P��Ԃ�
	}
	else
	{
		return routeList.front();
	}

}