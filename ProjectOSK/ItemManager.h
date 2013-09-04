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
	void SetItem(const Block &block);
	void Draw();
	void CheckHitCharactor(Player *player);
	ItemManager(void);
	~ItemManager(void);
};

