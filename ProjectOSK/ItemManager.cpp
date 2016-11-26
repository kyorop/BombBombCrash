#include "ItemManager.h"
#include "Item.h"
#include "GameConstant.h"

using namespace BombBombCrash;

ItemManager::ItemManager(void)
	:items()
{
	for (int i = 0; i < itemNum; i++)
	{
		auto item = std::make_shared<Item>();
		items.push_back(item);
	}
}

ItemManager::~ItemManager(void)
{
}

void ItemManager::Initialize(const Block &block)
{
	std::vector<int> i_block;
	std::vector<int> j_block;
	std::vector<int> history;

	for (int i = 0; i < BombBombCrash::MAP_ROW; i++)
	{
		for (int j = 0; j < BombBombCrash::MAP_LINE; j++)
		{
//			if(block.IsSoftBlock(i, j))
			{
				i_block.push_back(i);
				j_block.push_back(j);
			}
		}
	}

	for (int k = 0; k < itemNum; k++)
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
		items[k]->SetX(32 * j_block[m]);
		items[k]->SetY(32 * i_block[m]);
		items[k]->SetExists(1);
	}
}