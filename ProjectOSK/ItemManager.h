#pragma once
#include "IDrawable.h"
#define ITEMNUM 30

class Item;
class Block;
class Player;
class Charactor;
class ItemManager:
	virtual public IDrawable
{
private:
	Item *item[ITEMNUM];

public:

	Item* GetItemInstance(int index)const;
	void SetItem(const Block &block);
	void Draw();
    void CheckHitCharactor(Charactor *charctor)const;
	int GetBombState()const;//FALSEのボムアイテム数を返す
	int GetFireState()const;//FALSEの火力アイテム数を返す
	int GetSpeedState()const;//FALSEのスピードアイテム数を返す
	int GetCharactorHitBombNum()const;
	int GetCharactorHitFireNum()const;
	int GetCharactorHitSpeedNum()const;
	ItemManager(void);
	~ItemManager(void);
};

