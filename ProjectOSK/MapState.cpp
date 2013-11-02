#include "MapState.h"

MapState::MapState(void)
{
	for(int i=0;i<row;++i)
	{
		for(int j=0; j<line; ++j)
		{
			for(int k=0; j<objects; ++j)
			{
				for(int l=0; l<topic; ++l)
					mapState[i][j][k][l] = 0;
			}
		}
	}
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


void MapState::Finalize()
{
	for(int i=0;i<row;++i)
	{
		for(int j=0; j<line; ++j)
		{
			for(int k=0; j<objects; ++j)
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

