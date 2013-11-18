#include "MapState.h"
#include "Player.h"
#include "Enemy.h"
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
	bomb.clear();
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


void MapState::Update()
{
	playerInfo->x = player->GetX();
	playerInfo->y = player->GetY();
	playerInfo->flag = player->GetFlag();
	playerInfo->bombLevel = player->GetBombNum();
	playerInfo->fireLevel = player->GetFireLevel();
	playerInfo->speedLevel = player->GetMV();

	if(!enemy.empty())
	{
		std::list<const Charactor*>::iterator itrEnemy = enemy.begin();
		while (itrEnemy != enemy.end())	
		{
			if((*itrEnemy)->GetFlag() == 0)
			{
				itrEnemy = enemy.erase(itrEnemy);
				if(!enemy.empty())
					++itrEnemy;
				else
					break;
			}
			else
				++itrEnemy;
		}
	}

}