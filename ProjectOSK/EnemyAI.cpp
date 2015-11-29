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
#include "GetItem.h"
#include <typeinfo.h>


EnemyAI::EnemyAI(const Enemy& myself)
	:nextState(IStateChanger::NOCHAGE),
	state(new BreakBlock(this, myself)),
	myself(myself)
{
}

EnemyAI::~EnemyAI(void)
{
	delete state;
}


void EnemyAI::UpdateState()
{
	if(myself.GetX()%32 == 0 && myself.GetY()%32 == 0)
	{
		if(nextState != IStateChanger::NOCHAGE)
		{
			delete state;
			switch(nextState)
			{
			case IStateChanger::ATTACK:
				state = new AttackOtherCharacter(this, myself);
				break;
			case IStateChanger::AVOID:
				state =new Avoid(this, myself);
				break;
			case IStateChanger::BREAKBLOCK:
				state = new BreakBlock(this, myself);
				break;
			case IStateChanger::GETITEM:
				state = new GetItem(this, myself);
				break;
			}
			nextState = IStateChanger::NOCHAGE;
		}
	}
}


void EnemyAI::ChangeState(int next)
{
	nextState = next;
}

void EnemyAI::Analyse(const Enemy &myself)
{
	state->Analyse();
	UpdateState();
}

int EnemyAI::GetAction(const Enemy &myself)
{
	return state->GetRoute();
}
