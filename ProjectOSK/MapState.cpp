#include "MapState.h"
#include "GameConstant.h"
#include "Player.h"
#include "Enemy.h"
#include "Bomb.h"
#include "IGettable.h"
#include <typeinfo>

MapState::MapState(void)
	:player(),
	playerInfo()
{
}

MapState::MapState(const MapState &ms)
{
}

MapState::~MapState(void)
{
}

void MapState::SetState(int x, int y, int object, int state, int option)
{
	int i=y/32;
	int j=x/32;
	if( !(i < 0 || row < i || j < 0 || line < j) )
		mapState[i][j][object][option] = state;
}


void MapState::InitOneObject(object kind)
{
	for (int i = 0; i < GameConst::MAP_ROW; ++i)
	{
		for (int j = 0; j < GameConst::MAP_LINE; ++j)
		{
			mapState[i][j][kind][0] = 0;
			mapState[i][j][kind][1] = 0;
		}
	}
}

void MapState::Initialize()
{
	for(int i=0;i<row;++i)
	{
		for(int j=0; j<line; ++j)
		{
			for(int k=0; k<objects; ++k)
			{
				for(int l=0; l<topic; ++l)
					mapState[i][j][k][l] = 0;
			}
		}
	}
	playerInfo = new PlayerState();
}

void MapState::Finalize()
{
	bomb.clear();
	enemy.clear();
	delete playerInfo;
	for(int i=0;i<row;++i)
	{
		for(int j=0; j<line; ++j)
		{
			for(int k=0; k<objects; ++k)
			{
				for(int l=0; l<topic; ++l)
					mapState[i][j][k][l] = 0;
			}
		}
	}
}





void MapState::SetMapState(int x, int y, int state, int option)
{
	SetState(x, y, MAP, state);
}

void MapState::SetBlockState(int x, int y, int state, int option)
{
	SetState(x, y, BLOCK,state);
}

void MapState::SetItemState(int x, int y, int state, int option)
{
	SetState(x, y, ITEM,state);
}

void MapState::SetCharactorState(int x, int y, int state,int option)
{
	SetState(x, y, CHARACTOR, state);
}

void MapState::SetBombState(int x, int y, int state, int option)
{	
	SetState(x, y, BOMB,state,option);
}

void MapState::SetFireState(int x, int y, int state, int option)
{
	SetState(x, y, FIRE,state);
}

int MapState::GetState(int i, int j, int object, int option)
{
	if(i < 0 || row < i || j < 0 || line < j)
		return -1;
	else
		return MapState::mapState[i][j][object][option];
}


void MapState::RegisterWithCharacter(const Charactor* pCharactor)
{
	const type_info& charaType = typeid(*pCharactor);

	if(charaType == typeid(Player))
		player = pCharactor;
	else if(charaType == typeid(Enemy))
		enemy.push_back(pCharactor);
}


void MapState::Register(IGettable* anythigGettable)
{
	const type_info& type = typeid(*anythigGettable);

	if(type == typeid(Bomb))
		bomb.push_back(dynamic_cast<Bomb*>(anythigGettable));
}


void MapState::Update()
{
	playerInfo->x = player->GetX();
	playerInfo->y = player->GetY();
	playerInfo->flag = player->GetFlag();
	playerInfo->bombLevel = player->GetBombNum();
	playerInfo->fireLevel = player->GetFireLevel();
	playerInfo->speedLevel = player->GetMV();


	InitOneObject(BOMB);
//	std::list<const Bomb*>::iterator itr = bomb.begin();
	for (auto& b : bomb)
	{
		if (b->GetFlag())
		{
			int x_center = (b->GetX() + b->GetX() + 32) / 2;
			int y_center = (b->GetY() + b->GetY() + 32) / 2;
			int i_center = x_center / 32;
			int j_center = y_center / 32;
			SetState(x_center, y_center, BOMB, 1);
			SetState(x_center, y_center, BOMB, b->GetFireLevel(), 1);
		}
	}

//	for(itr; itr != bomb.end(); ++itr)
//	{
//		if( (*itr)->GetFlag() == 1 )
//		{
//			int x_center = ( (*itr)->GetX() + (*itr)->GetX()+32 ) / 2;
//			int y_center = ( (*itr)->GetY() + (*itr)->GetY()+32 ) / 2;
//			int i_center = x_center / 32;
//			int j_center = y_center / 32;
//			SetState(x_center, y_center, BOMB, 1);
//			SetState(x_center, y_center, BOMB, (*itr)->GetFireLevel(), 1);
//		}
//	}

	if(!enemy.empty())
	{
		std::list<const Charactor*>::iterator itrEnemy = enemy.begin();
		while (itrEnemy != enemy.end())	
		{
			if((*itrEnemy)->GetFlag() == 0)
			{
				itrEnemy = enemy.erase(itrEnemy);
				if(enemy.empty())
					break;
			}
			else
				++itrEnemy;
		}
	}

}