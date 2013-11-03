#include "EnemyAI.h"
#include "MapState.h"
#include "Enemy.h"
#include "Dijkstra.h"
#include "Search.h"
#include "Route.h"
#include "Target.h"
#include "Avoid.h"
#include "StopRoute.h"
#include "GameConstant.h"
#include "DangerState.h"
#include "State.h"
#include "AttackOtherCharacter.h"
#include "BreakBlock.h"
#include "DxLib.h"


EnemyAI::EnemyAI()
	:nextState(IStateChanger::NOCHAGE),
	state(new BreakBlock(this))
{
}

EnemyAI::~EnemyAI(void)
{
	delete state;
}


void EnemyAI::UpdateState()
{
	if(nextState != IStateChanger::NOCHAGE)
	{
		delete state;
		switch(nextState)
		{
		case IStateChanger::ATTACK:
			state = new AttackOtherCharacter(this);
			break;
		case IStateChanger::AVOID:
			state =new Avoid(this);
			break;
		}
		nextState = IStateChanger::NOCHAGE;
	}
}


void EnemyAI::ChangeState(int next)
{
	nextState = next;
}

void EnemyAI::Analyse(const Enemy &myself)
{
	UpdateState();
	state->Analyse(myself);
}

int EnemyAI::GetAction(const Enemy &myself)
{
	return state->GetRoute(myself);
}


