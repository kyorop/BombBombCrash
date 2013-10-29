#pragma once
#include "IDrawable.h"
#include "IRegister.h"
#define ITEMNUM 20

class Item;
class Block;
class Player;
class Charactor;
class Map;
class ItemManager:
	virtual public IDrawable, virtual public IRegister
{
private:
	Item *item[ITEMNUM];

public:

	Item* GetItemInstance(int index)const;
	void SetItem(const Block &block);
	void Draw();
    //void CheckHitCharactor(Charactor *charctor)const;
	int GetBombState()const;//FALSE�̃{���A�C�e������Ԃ�
	int GetFireState()const;//FALSE�̉ἨA�C�e������Ԃ�
	int GetSpeedState()const;//FALSE�̃X�s�[�h�A�C�e������Ԃ�
	int GetCharactorHitBombNum()const;
	int GetCharactorHitFireNum()const;
	int GetCharactorHitSpeedNum()const;
	ItemManager(void);
	~ItemManager(void);
	void Register(void);
};

