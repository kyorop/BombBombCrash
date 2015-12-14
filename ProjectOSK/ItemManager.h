#pragma once
#include "Item.h"

namespace BombBombCrash
{
	class Item;
	class Block;
	class Player;
	class Character;
	class Map;

	class ItemManager
	{
	public:
		static const int itemNum = 20;

	private:
		std::vector<std::shared_ptr<Item>> items;

	public:

		Item* GetItemInstance(int index)const;
		void Initialize(const Block &block);
		//void CheckHitCharactor(Charactor *charctor)const;
		int GetBombState()const;//FALSEのボムアイテム数を返す
		int GetFireState()const;//FALSEの火力アイテム数を返す
		int GetSpeedState()const;//FALSEのスピードアイテム数を返す
		int GetCharactorHitBombNum()const;
		int GetCharactorHitFireNum()const;
		int GetCharactorHitSpeedNum()const;
		ItemManager(void);
		~ItemManager(void);
	};
}




