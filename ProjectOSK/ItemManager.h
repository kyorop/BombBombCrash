#pragma once
#define ITEMNUM 30

class Item;
class Block;
class Player;
class Charactor;
class ItemManager
{
private:
	Item *item[ITEMNUM];

public:

	Item* GetFirstItemPointa();
	void SetItem(const Block &block);
	void Draw();
    int CheckHitCharactor(Charactor &charctor)const;
	int GetBombState()const;//FALSEのボムアイテム数を返す
	int GetFireState()const;//FALSEの火力アイテム数を返す
	int GetSpeedState()const;//FALSEのスピードアイテム数を返す
	ItemManager(void);
	~ItemManager(void);
};

