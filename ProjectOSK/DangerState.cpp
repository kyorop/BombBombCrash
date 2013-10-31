#include "DangerState.h"
#include "MapState.h"
#include <iostream>

DangerState::DangerNode::DangerNode():
	danger(0),
	i_brastCenter(-1),
	j_brastCenter(-1)
{
}

DangerState::DangerState(void)
{
}

DangerState::~DangerState(void)
{
}

void DangerState::Update()
{
	for (int i = 0; i < GameConst::MAP_ROW; ++i)
	{
		for (int j = 0; j < GameConst::MAP_LINE; ++j)
		{
			//中心が消えたら他も全部消す
			if(node[i][j].danger == 1 && MapState::GetInstance()->GetState(node[i][j].i_brastCenter, node[i][j].j_brastCenter, BOMB) == 0)
			{
				node[i][j].danger = 0; 
			}
		}
	}

	for (int i = 0; i < GameConst::MAP_ROW; ++i)
	{
		for (int j = 0; j < GameConst::MAP_LINE; ++j)
		{
			if(MapState::GetInstance()->GetState(i, j, FIRE) == 1)
				fireNode[i][j] = 1;
			else
				fireNode[i][j] = 0;
		}
	}

	for (int i_node= 0; i_node < GameConst::MAP_ROW; ++i_node)
	{
		for (int j_node = 0; j_node < GameConst::MAP_LINE; ++j_node)
		{
			//ボムが置かれているなら
			if(MapState::GetInstance()->GetState(i_node, j_node, BOMB) == 1)
			{
				int fireLevel = MapState::GetInstance()->GetState(i_node, j_node, BOMB, 1);
				//ボムが置かれた場所は常に１にしておく
				node[i_node][j_node].danger = 1;
				node[i_node][j_node].i_brastCenter = i_node;
				node[i_node][j_node].j_brastCenter = j_node;

				//爆心地を中心に火力分だけ四方を危険地域に設定

				//中心から右
				for (int i = i_node+1; i <= i_node+fireLevel; ++i)
				{
					if(0 <= i && i < GameConst::MAP_ROW)
					{
						if(MapState::GetInstance()->GetState(i, j_node, MAP) == 1
							|| MapState::GetInstance()->GetState(i, j_node, BLOCK) == 1
							||MapState::GetInstance()->GetState(i, j_node, ITEM) == 1
							||MapState::GetInstance()->GetState(i, j_node, BOMB) == 1
							//||MapState::GetInstance()->GetState(i, j_node, CHARACTOR) == 1
							)
						{
							break;
						}
						else
						{
							node[i][j_node].danger = 1;
							node[i][j_node].i_brastCenter = i_node;
							node[i][j_node].j_brastCenter = j_node;
						}
					}
				}

				//中心から左
				for (int i=i_node-1; i >= i_node - fireLevel ; --i)
				{
					if(0 <= i && i < GameConst::MAP_ROW)
					{
						if(MapState::GetInstance()->GetState(i, j_node, MAP) == 1
							|| MapState::GetInstance()->GetState(i, j_node, BLOCK) == 1
							||MapState::GetInstance()->GetState(i, j_node, ITEM) == 1
							||MapState::GetInstance()->GetState(i, j_node, BOMB) == 1
							//||MapState::GetInstance()->GetState(i, j_node, CHARACTOR) == 1
							)
						{
							break;
						}
						else
						{
							node[i][j_node].danger = 1;
							node[i][j_node].i_brastCenter = i_node;
							node[i][j_node].j_brastCenter = j_node;
						}
					}
				}

				//中心から下
				for (int j=j_node+1; j <= j_node+fireLevel; ++j)
				{
					if(0 <= j && j < GameConst::MAP_LINE)
					{
						if(MapState::GetInstance()->GetState(i_node, j, MAP) == 1
							|| MapState::GetInstance()->GetState(i_node, j, BLOCK) == 1
							||MapState::GetInstance()->GetState(i_node, j, ITEM) == 1
							||MapState::GetInstance()->GetState(i_node, j, BOMB) == 1
							//||MapState::GetInstance()->GetState(i_node, j, CHARACTOR) == 1
							)
						{
							break;
						}
						else
						{
							node[i_node][j].danger = 1;
							node[i_node][j].i_brastCenter = i_node;
							node[i_node][j].j_brastCenter = j_node;
						}
					}
				}

				//中心から上
				for (int j=j_node-1; j >= j_node - fireLevel ; --j)
				{
					if(0 <= j && j < GameConst::MAP_LINE)
					{
						if(MapState::GetInstance()->GetState(i_node, j, MAP) == 1
							|| MapState::GetInstance()->GetState(i_node, j, BLOCK) == 1
							||MapState::GetInstance()->GetState(i_node, j, ITEM) == 1
							||MapState::GetInstance()->GetState(i_node, j, BOMB) == 1
							//||MapState::GetInstance()->GetState(i_node, j, CHARACTOR) == 1
							)
						{
							break;
						}
						else
						{
							node[i_node][j].danger = 1;
							node[i_node][j].i_brastCenter = i_node;
							node[i_node][j].j_brastCenter = j_node;
						}
					}
				}
			}
		}
	}
}

int DangerState::GetDangerState(int i , int j)const
{
	if(0 <= i && i < GameConst::MAP_ROW && 0 <= j && j < GameConst::MAP_LINE)
	{
		return node[i][j].danger;
	}
	else
	{
		return -1;
	}
}

int DangerState::GetFireState(int i, int j)const
{
	if(0 <= i && i < GameConst::MAP_ROW && 0 <= j && j < GameConst::MAP_LINE)
	{
		return fireNode[i][j];
	}
	else
	{
		return -1;
	}	
}