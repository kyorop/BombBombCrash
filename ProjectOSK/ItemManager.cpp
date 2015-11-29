#include "ItemManager.h"
#include "Item.h"
#include "Block.h"
#include "Player.h"
#include "Charactor.h"
#include "MapState.h"
#include "Collision.h"
#include "Map.h"
#include <list>


ItemManager::ItemManager(void)
	:item()
{
	for(int i=0; i<ITEMNUM; i++)
		item[i] = new Item;

}

ItemManager::~ItemManager(void)
{
	for(int i=0; i<ITEMNUM; i++)
		delete item[i];
}

void ItemManager::SetItem(const Block &block)
{
	std::vector<int> i_block;
	std::vector<int> j_block;
	std::vector<int> history;

	for (int i = 0; i < GameConst::MAP_ROW; i++)
	{
		for (int j = 0; j < GameConst::MAP_LINE; j++)
		{
			if(block.IsSoftBlock(i, j))
			{
				i_block.push_back(i);
				j_block.push_back(j);
			}
		}
	}

	for (int k = 0; k < ITEMNUM; k++)
	{
		int m = -1;
		while(m == -1)
		{
			m = GetRand(i_block.size()-1);
			for (int count = 0,size = history.size(); count < size; count++)
			{
				if(m == history[count])
				{
					m = -1;
					break;
				}
			}
		}
		history.push_back(m);
		item[k]->SetX(32 * j_block[m]);
		item[k]->SetY(32 * i_block[m]);
		item[k]->SetFlag(1);
	}
}

void ItemManager::Draw()
{
	for(int i=0; i<ITEMNUM; ++i)
	{
			item[i]->Draw();
	}
}


void ItemManager::Register(void)
{
	for(int i=0; i<ITEMNUM; ++i)
	{
		if(this->item[i]->GetFlag() == 1)
			MapState::GetInstance()->SetItemState(this->item[i]->GetX(), this->item[i]->GetY(),1);
		else if(this->item[i]->GetFlag() == 0)
			MapState::GetInstance()->SetItemState(this->item[i]->GetX(), this->item[i]->GetY(),0);
	}
}
