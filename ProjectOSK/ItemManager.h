#pragma once
#include "Item.h"

namespace BombBombCrash
{
	class Item;
	class Block;
	class Map;

	class ItemManager
	{
	private:
		static const int itemNum = 20;
//		std::vector<std::shared_ptr<Block>> map;
		std::vector<std::shared_ptr<Item>> items;

	public:
		std::vector<std::shared_ptr<Item>> Create();
		ItemManager();
		~ItemManager();
	};
}




