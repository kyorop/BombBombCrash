#pragma once
#define ITEMNUM 10

class Item;
class Block;
class Player;
class ItemManager
{
private:
	Item *item[ITEMNUM];

public:
	Item* GetFirstItemPointa();
	void SetItem(const Block &block);
	void Draw();
    int CheckHitCharactor(Player &player)const;
	int GetNowBombNum();
	int GetNowFireNum();
	int GetNowSpeedNum();
	ItemManager(void);
	~ItemManager(void);
};

