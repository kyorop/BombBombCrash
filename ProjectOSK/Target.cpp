#include "Target.h"
#include "Search.h"
#include "Dijkstra.h"
#include "Enemy.h"
#include "GameConstant.h"
#include "MapState.h"
#include "DxLib.h"

Target::Target(void):
	i_toList(),
	j_toList(),
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

int Target::CheckExistenceOfCharacterAroundMyself(int i_now, int j_now, int *i_to, int *j_to)
{
	int success = 0;
	for(int i=i_now-radiusOfSearch; i<=i_now+radiusOfSearch; ++i)
	{
		for(int j=j_now-radiusOfSearch; j<=j_now+radiusOfSearch; ++j)
		{
			if(i != i_now && j != j_now)
			{
				if(MapState::GetInstance()->GetState(i, j, CHARACTOR) == 1)//���̃L�����N�^�[����������
				{
					if(search->CheckAbleToGoTo(i_now, j_now, i, j) == 1)//�����ɍs���邩���ׂ�
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

void Target::DecideGoal(const Enemy &myself)
{
	hasCalculated = 0;
}

void Target::SetRoute(const Enemy &myself)
{
	//������
	i_toList.clear();
	j_toList.clear();
	//������
	routeList.clear();

	int x_center = (myself.GetX()+myself.GetX()+32)/2;
	int y_center = (myself.GetY()+myself.GetY()+32)/2;
	int i_center = y_center/32;
	int j_center = x_center/32;

	int i_to;
	int j_to;
	if(CheckExistenceOfCharacterAroundMyself(i_center, j_center, &i_to, &j_to) == 1)
	{
		dijkstra->SearchShortestPath(i_center, j_center, i_to, j_to, &routeList);
		routeList.push_back(BOMBSET);
	}
	else if(search->SetGoal(y_center/32, x_center/32, &i_toList, &j_toList) == 1)
	{
		//�ړI�n�͌��̓����痐���Ō��߂�
		rand = GetRand(i_toList.size() - 1);

		//�ŒZ�o�H�̃Z�b�g
		dijkstra->SearchShortestPath(y_center/32, x_center/32, i_toList[rand], j_toList[rand], &routeList);
		routeList.push_back(BOMBSET);
	}
}

int Target::GetRoute(const Enemy &myself)
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
					return BOMBSET;
				//case BOMBSETOFF:
				//	routeList.pop_front();
				//	return BOMBSETOFF;
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
		return -1;		//���X�g����Ȃ�I��(�G���[)�Ƃ��ā|�P��Ԃ�
	}
	else
	{
		return routeList.front();
	}
}