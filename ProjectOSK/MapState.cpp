#include "MapState.h"
#include "Bomb.h"
#include "IGettable.h"
#include "GameConstant.h"

MapState::MapState(void)
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


void MapState::Register(Bomb* pBomb)
{
	bomb.push_back(pBomb);
}


void MapState::Update()
{
	for (int i = 0; i < GameConst::MAP_ROW; ++i)
	{
		for (int j = 0; j < GameConst::MAP_LINE; ++j)
		{
			mapState[i][j][BOMB][0] = 0;
			mapState[i][j][BOMB][1] = 0;
		}
	}

	std::list<Bomb*>::iterator itr = bomb.begin();
	for(itr; itr != bomb.end(); ++itr)
	{
		if( (*itr)->GetFlag() == 1 )
		{
			int x_center = ( (*itr)->GetX() + (*itr)->GetX()+32 ) / 2;
			int y_center = ( (*itr)->GetY() + (*itr)->GetY()+32 ) / 2;
			int i_center = x_center / 32;
			int j_center = y_center / 32;
			SetState(x_center, y_center, BOMB, 1);
			SetState(x_center, y_center, BOMB, (*itr)->GetFireLevel(), 1);
		}
	}
}


void MapState::Finalize()
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

