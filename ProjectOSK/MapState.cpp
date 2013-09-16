#include "MapState.h"
enum object
{
	MAP,
	BLOCK,
	ITEM,
	CHARACTOR,
	BOMB,
	FIRE,
};

int MapState::mapState[ROW][LINE][ELEMENT][TOPIC];

MapState::MapState(void)
{
	for(int i=0;i<ROW;++i)
	{
		for(int j=0; j<LINE; ++j)
		{
			for(int k=0; j<ELEMENT; ++j)
			{
				for(int l=0; l<TOPIC; ++l)
					mapState[i][j][k][l] = 0;
			}
		}
	}
}

MapState::MapState(const MapState &ms)
{
}

void MapState::Initialize()
{
	
}

//MapState* MapState::GetInstance()
//{
//	static MapState msInstance;
//	return &msInstance;
//}

void MapState::SetState(int x, int y, int object, int state, int option)
{
	int i=y/32;
	int j=x/32;
	if( !(i < 0 || ROW < i || j < 0 || LINE < j) )
	{
		MapState::mapState[i][j][object][option] = state;
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

void MapState::SetBombState(int x, int y, int state, int fireLevel)
{
	SetState(x, y, BOMB,state);
	MapState::mapState[y/32][x/32][BOMB][1] = fireLevel;
}

void MapState::SetFireState(int x, int y, int state, int option)
{
	SetState(x, y, FIRE,state);
}

int MapState::GetState(int i, int j, int object, int option)
{
	if(i < 0 || ROW < i || j < 0 || LINE < j)
		return -1;
	else
		return MapState::mapState[i][j][object][option];
}

MapState::~MapState(void)
{
}