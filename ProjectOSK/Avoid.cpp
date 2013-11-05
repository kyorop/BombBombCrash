#include "Avoid.h"
#include "Search.h"
#include "Dijkstra.h"
#include "Enemy.h"
#include "MapState.h"
#include "DangerState.h"

Avoid::Avoid(IStateChanger *stateMrg)
	:State(stateMrg)
{
}

Avoid::~Avoid(void)
{
}


void Avoid::ChangeState()
{
	//�L�����N�^�[�����傤�ǃ}�X�s�b�^���ɂ��鎞�����X�e�[�g�̐؂�ւ����s��
	if(x_now%32 == 0 && y_now%32 == 0)
	{
		if(DangerState::GetInstance()->GetDangerState(i_center, j_center) == 1)
		{
		}
		else/* if(CheckAroundMyself(i_center, j_center, MapState::BLOCK, 8) == 1 )*/
		{
			stateMrg->ChangeState(IStateChanger::BREAKBLOCK);
			
			//�؂�ւ������܂�����A����ȏ�ړ����Ȃ��悤�ɂ���
			routeList.clear();
			reset = 0;
		}
	}
}


void Avoid::Analyse(const Enemy &myself)
{
	x_now = myself.GetX();
	y_now = myself.GetY();
	x_center = (myself.GetX()+myself.GetX()+32)/2;
	y_center = (myself.GetY()+myself.GetY()+32)/2;
	i_center = y_center/32;
	j_center = x_center/32;
	
	ChangeState();
	
	if(reset == 1)
	{
		routeList.clear();
		//���[�g�Z�b�g
		if(search->SetEscapeRouteWhenInDanger(y_now/32, x_now/32, &routeList) == 1)
		{
			routeList.push_back(GameConst::EnemyAction::STOP);
			reset = 0;
		}
	}
}