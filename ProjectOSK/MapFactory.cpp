#include "MapFactory.h"
#include "GameConstant.h"
#include "Image.h"
#include "Item.h"
#include "GameManager.h"
#include "HardBlock.h"
#include "BreakableBlock.h"
#include "MapObject.h"
#include <random>

using namespace BombBombCrash;

const int MapFactory::map[MAP_ROW][MAP_LINE] =
{
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 1, 1,
	1, 1, 0, 1, 2, 1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
	1, 1, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 1, 1,
	1, 1, 2, 1, 2, 1, 2, 1, 0, 1, 0, 1, 0, 1, 2, 1, 1,
	1, 1, 2, 0, 2, 0, 2, 0, 0, 0, 2, 2, 2, 0, 2, 1, 1,
	1, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 2, 1, 1,
	1, 1, 2, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 0, 2, 1, 1,
	1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 1,
	1, 1, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 1, 1,
	1, 1, 0, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 1, 1,
	1, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};


ln::Vector2 MapFactory::ConvertToBlockPos(const int i, const int j)
{
	return ln::Vector2(GameConstant::BlockWidth*j, GameConstant::BlockHeight*i);
}


void MapFactory::Create()
{

	//		int temp[MAP_ROW][MAP_LINE] =
	//		{
	//			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	//			1, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 0, 0, 1, 1,
	//			1, 1, 0, 1, 2, 1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
	//			1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 1, 1,
	//			1, 1, 2, 1, 2, 1, 2, 1, 0, 1, 0, 1, 0, 1, 2, 1, 1,
	//			1, 1, 2, 0, 2, 0, 2, 0, 0, 0, 2, 2, 2, 0, 2, 1, 1,
	//			1, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 2, 1, 1,
	//			1, 1, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 0, 2, 1, 1,
	//			1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 1,
	//			1, 1, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 1, 1,
	//			1, 1, 0, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 1, 1,
	//			1, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 1, 1,
	//			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	//		};

	AnimationClip items = Image::GetInstance()->Load("Images\\itemup.bmp", 3, 3, 1, 32, 32);
	AnimationClip fire_up_clip(items.get_handle(0));
	AnimationClip bomb_up_clip(items.get_handle(1));
	AnimationClip speed_up_clip(items.get_handle(2));

	std::vector<std::pair<int, int>> breakable_block_entries;
	for (size_t i = 0; i < MAP_ROW; ++i)
	{
		for (size_t j = 0; j < MAP_LINE; ++j)
		{
			if (map[i][j] == 2)
			{
				breakable_block_entries.emplace_back(i, j);
			}
		}
	}
	std::shuffle(begin(breakable_block_entries), end(breakable_block_entries), std::mt19937());
	const size_t item_num = 20;
	const size_t item_type = 3;
	const size_t each_item_num = item_num / item_type;
	std::list<MapObject::ObjectType> item_types(each_item_num, MapObject::ObjectType::BombUpItem);
	item_types.splice(begin(item_types), std::list<MapObject::ObjectType>(item_num / item_type, MapObject::ObjectType::FireUpItem));
	item_types.splice(begin(item_types), std::list<MapObject::ObjectType>(item_num / item_type + item_num % item_type, MapObject::ObjectType::SpeedUpItem));
	
	breakable_block_entries.erase(begin(breakable_block_entries), end(breakable_block_entries) - item_num);
	auto item_type_itr = begin(item_types);

	for (int i = 0; i < MAP_ROW; ++i)
	{
		for (int j = 0; j < MAP_LINE; ++j)
		{
			if (map[i][j] == 1)
			{
				GameManager::Instance().AddTask(std::make_unique<HardBlock>(ConvertToBlockPos(i, j)));
			}
			else if (map[i][j] == 2)
			{
				auto position = ConvertToBlockPos(i, j);
				if (find(begin(breakable_block_entries), end(breakable_block_entries), std::make_pair(i, j)) != end(breakable_block_entries))
				{
					AnimationClip item_clip;
					switch (*item_type_itr)
					{
					case MapObject::ObjectType::BombUpItem:item_clip = bomb_up_clip; break;
					case MapObject::ObjectType::FireUpItem:item_clip = fire_up_clip; break;
					case MapObject::ObjectType::SpeedUpItem:item_clip = speed_up_clip; break;
					}
					auto item = std::make_unique<Item>(item_clip, *item_type_itr);
					++item_type_itr;
					item->SetPosition(position);
					GameManager::Instance().AddTask(std::make_unique<BreakableBlock>(position, move(item)));
				}
				else
				{
					GameManager::Instance().AddTask(std::make_unique<BreakableBlock>(position));
				}
			}
		}
	}
}
