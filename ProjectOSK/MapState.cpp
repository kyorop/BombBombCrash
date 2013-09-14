#include "MapState.h"
enum
{
	MAP,
	BLOCK,
	ITEM,
	CHARACTOR,
	BOMB,
	FIRE,
};

MapState::MapState(void)
{
	for(int i=0;i<ROW;++i)
	{
		for(int j=0; j<LINE; ++j)
		{
			for(int k=0; j<OBJECT; ++j)
			{
				for(int l=0; l<TOPIC; ++l)
					mapState[i][j][k][l] = 0;
			}
		}
	}
}

MapState* MapState::GetInstance()
{
	static MapState msInstance;
	return &msInstance;
}

void MapState::SetState(int x, int y, int object, int state, int option=0)
{
	this->mapState[y/32][x/32][object][option] = state;
}

void MapState::SetMapState(int x, int y, int state, int option=0)
{
	SetState(x, y, MAP, state);
}

void MapState::SetBlockState(int x, int y, int state, int option=0)
{
	SetState(x, y, BLOCK,state);
}

void MapState::SetItemState(int x, int y, int state, int option)
{
	SetState(x, y, ITEM,state);
}

void MapState::SetCharactorState(int x, int y, int state,int option=0)
{
	SetState(x, y, CHARACTOR, state);
}

void MapState::SetBombState(int x, int y, int state, int fireLevel)
{
	SetState(x, y, BOMB,state);
	this->mapState[y/32][x/32][BOMB][1] = fireLevel;
}

void MapState::SetFireState(int x, int y, int state, int option)
{
	SetState(x, y, FIRE,state);
}

MapState::~MapState(void)
{
}