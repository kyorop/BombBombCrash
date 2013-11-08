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
#include <typeinfo.h>

//State* EnemyAI::state;

EnemyAI::EnemyAI()
	:nextState(IStateChanger::NOCHAGE)
	//state(new BreakBlock(this))
{
	state = new BreakBlock(this);
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
		case IStateChanger::BREAKBLOCK:
			state = new BreakBlock(this);
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


//void EnemyAI::ShowState(int x, int y)
//{
//	int color = GetColor(0, 255, 102);
//	
//	if(state != 0)
//	{
//		const type_info &type = typeid( *state );
//		
//		if(type == typeid(Avoid))
//			DrawFormatString(x, y, color,"Avoid");
//		else if(type == typeid(BreakBlock))
//			DrawFormatString(x, y, color,"BreakBlock");
//		else if(type == typeid(AttackOtherCharacter))
//			DrawFormatString(x, y, color,"AttackOtherCharacter");
//	}
//	else
//		DrawFormatString(x, y, color,"NULL");
//}
