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
	int GetBombState()const;//FALSE�̃{���A�C�e������Ԃ�
	int GetFireState()const;//FALSE�̉ἨA�C�e������Ԃ�
	int GetSpeedState()const;//FALSE�̃X�s�[�h�A�C�e������Ԃ�
	int GetCharactorHitBombNum()const;
	int GetCharactorHitFireNum()const;
	int GetCharactorHitSpeedNum()const;
	ItemManager(void);
	~ItemManager(void);
};

